#include "Application.h"

// TODO: NEED TO WRITE A TEXTURE HANDLER THAT DEALS WITH ALLOCATING + DEALLOCATING TEXTURES

// -------------------------------------------------------------------------------
// HELPER FUNCTIONS
// -------------------------------------------------------------------------------

// Callback function to adjust the viewport when the window is resized
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void CursorPositionCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    // Makes sure the user is in locked mouse mode before allowing unlimited mouse movement
    if (currentWindow->IsMouseLocked())
        Application::ProcessMouseInput((float)xposIn, (float)yposIn);
}

// -------------------------------------------------------------------------------
// WINDOW CLASS
// -------------------------------------------------------------------------------

Window::Window(int width, int height, const std::string& title)
    : m_WindowDimensions{width, height, 0, 0},
	  m_ScreenDimensions{(unsigned int) width, (unsigned int) height}
{
    if (!glfwInit())
    {
        LOG_ERR("Failed to initialize GLFW\n");
        m_Handle = nullptr;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, OPENGL_DEBUG_MODE);

    m_Handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    glfwSetWindowUserPointer(m_Handle, this); // Links Window class to the handle

    if (!m_Handle)
    {
        LOG_ERR("Failed to create GLFW Window!");
        return;
    }

    glfwMakeContextCurrent(m_Handle);
	glfwSwapInterval(0); // Disables VSync
    Init();
}

Window::~Window()
{
    if (m_Handle) glfwDestroyWindow(m_Handle);
}

// Sets the minimum window size and window callbacks
void Window::Init() const
{
    glfwSetWindowSizeLimits(m_Handle, WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetFramebufferSizeCallback(m_Handle, FramebufferSizeCallback);

	glfwSetCursorPosCallback(m_Handle, CursorPositionCallback);
}

GLFWwindow* Window::ReturnWindow() const { return m_Handle; }

// Swaps the front and back buffers (where everything is being drawn) of the window (double buffering)
void Window::SwapBuffers() const
{
    glfwSwapBuffers(m_Handle);
}

// Polls for and processes events (e.g keyboard input, mouse input, window resizing, etc.)
void Window::PollEvents() const
{
    glfwPollEvents();
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_Handle);
}

void Window::SetFullscreen()
{
    GLFWmonitor* currentMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* currentMode = glfwGetVideoMode(currentMonitor);

    if (!m_InFullscreen)
    {
        m_InFullscreen = true;
        
        // Caches the previous window size/position to be reset to if going back to windowed
        glfwGetWindowSize(m_Handle, &(m_WindowDimensions[0]), &(m_WindowDimensions[1]));
        glfwGetWindowPos(m_Handle, &(m_WindowDimensions[2]), &(m_WindowDimensions[3]));

        glfwSetWindowMonitor(m_Handle, currentMonitor, 0, 0, currentMode->width,
            currentMode->height, currentMode->refreshRate);
    }
    else
    {
        m_InFullscreen = false;
        glfwSetWindowMonitor(m_Handle, NULL, m_WindowDimensions[2], m_WindowDimensions[3], m_WindowDimensions[0],
            m_WindowDimensions[1], 0);
    }
}

void Window::ChangeMouseLock()
{
    double xPos, yPos;

    if (m_MouseLocked)
    {
        glfwGetCursorPos(m_Handle, &xPos, &yPos);
        Application::EnableFreeMouseMovement(xPos, yPos);

        m_MouseLocked = false;
        glfwSetInputMode(m_Handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        m_MouseLocked = true;
        glfwSetInputMode(m_Handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

// -------------------------------------------------------------------------------
// APPLICATION CLASS
// -------------------------------------------------------------------------------

// Static member initialization (via 9.4.2 of C++ standard)

// Holds the current window of the application (only one for now)
Window* Application::m_CurrentWindow;
Camera* Application::m_Camera;
TextureRenderer* Application::m_TextureRenderer;
MeshRenderer* Application::m_MeshRenderer;

bool Application::m_FirstMouse = true;
bool Application::m_RetrievedLibraries;
bool Application::m_AppRunning;

float Application::m_LastX;
float Application::m_LastY;

// Initialises the window instance of the application
bool Application::CreateWindow()
{
    m_CurrentWindow = new Window(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT, APP_NAME);
	m_LastX = (float)WINDOW_DEFAULT_WIDTH / 2.0f;
    m_LastY = (float)WINDOW_DEFAULT_HEIGHT / 2.0f;

    Application::InitialiseHandlers();

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        LOG_ERR("Failed to initialize GLAD\n");
        return false;
	}

	LOG_INFO("OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << " has been loaded.");

    m_RetrievedLibraries = true;

    return true;
}

// Initialises all handlers where necessary (e.g player controllers, camera controllers, etc.)
void Application::InitialiseHandlers()
{
	if (glfwRawMouseMotionSupported())
    {
        glfwSetInputMode(m_CurrentWindow->ReturnWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

    InputHandler::Init(m_CurrentWindow->ReturnWindow());
}

// Sets up default application system actions (e.g fullscreen, unlock mouse, etc.)
void Application::RegisterApplicationActions()
{
    ActionHandler::CreateAction(GLFW_KEY_F11, &Window::SetFullscreen, m_CurrentWindow, "Toggle Fullscreen");
    InputHandler::AttachAction(ActionHandler::RetrieveLastAction(), GLFW_PRESS);

    ActionHandler::CreateAction(GLFW_KEY_Z, &Window::ChangeMouseLock, m_CurrentWindow, "Set Mouse Lock");
    InputHandler::AttachAction(ActionHandler::RetrieveLastAction(), GLFW_PRESS);
}

void Application::EnableFreeMouseMovement(double xPos, double yPos)
{
    m_LastX = xPos;
    m_LastY = yPos;
    m_FirstMouse = true;
}

// Terminates the program when called (eventually need to refactor to delete renderers automatically when they go out of scope instead of manually deleting them here)
void Application::Shutdown()
{
    m_AppRunning = false;
    InputHandler::ReleaseAllActions();
    ActionHandler::RemoveAllActions();

	delete m_Camera;
	m_Camera = nullptr;

    delete m_TextureRenderer;
    m_TextureRenderer = nullptr;

    delete m_MeshRenderer;
	m_MeshRenderer = nullptr;

    delete m_CurrentWindow;
    m_CurrentWindow = nullptr;

    glfwTerminate();
}

// Main application loop
void Application::Run()
{
	// Used for presentation purposes only to give random forces to cubes, will be removed in the future when we have a proper physics system in place with more interesting interaction
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(-100.0f, 100.0f);

	auto randomForce = [&generator, &distribution]() { return distribution(generator); };

    GLCall(glEnable(GL_DEPTH_TEST))

	// m_CurrentWindow->ChangeMouseLock(); // Locks the mouse to the center of the window and hides it (for testing purposes only, need to change for the future)

	m_Camera = new Camera(glm::vec3(0.0f, 0.0f, 20.0f));

	m_TextureRenderer = new TextureRenderer();
    m_TextureRenderer->Init(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT);

    m_MeshRenderer = new MeshRenderer();
	m_MeshRenderer->Init(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT);
    
    Texture* testTexture = new Texture("assets/textures/maxwell.jpg");    
	float textureParameters[] = { 500.0f, 360.0f, 256.0f, 256.0f }; // xPos, yPos, width, height

    BoxMesh* meshList[MAX_ENTITIES] = {}; // Used to deallocate mesh memory later
    Entity* entityList[MAX_ENTITIES] = {}; // Used to deallocate entity memory later

	RigidBody* rigidBodyList[MAX_ENTITIES] = {}; // Used to give random forces to cubes later (for presentation purposes only)  

	// Initialises a grid of cubes with physics bodies for presentation purposes
    for (int i = 0; i < MAX_GRID_SIZE; i++)
    {
        for (int j = 0; j < MAX_GRID_SIZE; j++)
        {
			int currentIndex = (i * MAX_GRID_SIZE) + j;
            BoxMesh* testMesh = new BoxMesh(testTexture);
            meshList[currentIndex] = testMesh;

            testMesh->SetPosition(glm::vec3(-1.0f + (float) i, 0.0f, -1.0f + (float) j));

            glm::vec3 boxHalfExtents = testMesh->GetScale() * 0.5f; // Assuming the original cube mesh is a unit cube, we can calculate the half extents by multiplying the scale by 0.5
            Box* testBoxShape = new Box(boxHalfExtents, testMesh->GetScale());

            RigidBody* testDynamicRigidBody = new RigidBody((Shape*)testBoxShape, 1.0f, testMesh->GetPosition());
            rigidBodyList[currentIndex] = testDynamicRigidBody;

			Entity* testEntity = new Entity(testMesh, testDynamicRigidBody);
			entityList[currentIndex] = testEntity;

        }
	}
    
    LOG_INFO("Instantiated " << MAX_ENTITIES << " entities..");

    if (m_AppRunning) 
    {
        LOG_WARN("Application is already running!");
        return;
    }

    m_AppRunning = true;

    Application::RegisterApplicationActions();
	
    PhysicsEngine::Init();

    for (int i = 0; i < MAX_ENTITIES; i++)
    {
		RigidBody* currentBody = rigidBodyList[i];
        PhysicsEngine::AddRigidBody(currentBody);
        
        currentBody->AddForce(glm::vec3(randomForce(), randomForce() * 10.0f, randomForce())); // Adds an initial upward force to the cube for testing purposes only
        currentBody->AddTorque(glm::vec3(randomForce(), 0.0f, randomForce())); // Adds an initial torque to the cube for testing purposes only
    }

    // background colour (dark grey)
    GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
    int currentWindowWidth, currentWindowHeight;

    while (!m_CurrentWindow->ShouldClose())
    {
        glfwGetWindowSize(m_CurrentWindow->ReturnWindow(), &currentWindowWidth, &currentWindowHeight);
        m_CurrentWindow->SetScreenWidth(currentWindowWidth);
        m_CurrentWindow->SetScreenHeight(currentWindowHeight);

        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		// Used to ensure a fixed time step for physics simulation regardless of frame rate (via "Fix Your Timestep" method described by Gaffer on Games: https://gafferongames.com/post/fix_your_timestep/)
		static float timeAccumulator = 0.0f;
        
        TimeManager::Update();
		timeAccumulator += TimeManager::DeltaTime();

        while (timeAccumulator >= PhysicsEngine::GetPhysicsTimeStep())
        {
            PhysicsEngine::Step();
            timeAccumulator -= PhysicsEngine::GetPhysicsTimeStep();
		}

		// Syncs the entity's mesh position/rotation with the physics body's position/rotation and draws the mesh 
        // (eventually need to refactor to have a proper scene graph and render queue instead of doing this in the main loop here)
        for (int i = 0; i < MAX_ENTITIES; i++)
        { 
            entityList[i]->Sync();
            m_MeshRenderer->DrawCubeMesh(meshList[i], m_Camera->GetViewMatrix(), m_CurrentWindow->GetScreenWidth(), m_CurrentWindow->GetScreenHeight());
        }

        // m_TextureRenderer->Draw(testTexture, textureParameters);

		Application::ProcessKeyboardInput();

        m_CurrentWindow->SwapBuffers();
        m_CurrentWindow->PollEvents();
    }

	// Need to delete these automatically eventually via resource handlers instead of manually deleting them here

    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        delete entityList[i];
		entityList[i] = nullptr;

		delete meshList[i];
		meshList[i] = nullptr;
    }

    delete testTexture;
    testTexture = nullptr;

	PhysicsEngine::Shutdown();
    Application::Shutdown();
}

// -------------------------------------------------------------------------------
// APPLICATION CALLBACK FUNCTIONS
// -------------------------------------------------------------------------------

void Application::ProcessMouseInput(float xpos, float ypos)
{
    if (m_FirstMouse)
    {
        m_LastX = xpos;
        m_LastY = ypos;
        m_FirstMouse = false;
    }

    float xOffset = xpos - m_LastX;
    float yOffset = m_LastY - ypos; // reversed since y-coordinates go from bottom to top
    m_LastX = xpos;
    m_LastY = ypos;

	m_Camera->ProcessMouse(xOffset, yOffset);
}

// REFACTOR EVENTUALLY TO WORK WITH INPUT HANDLER INSTEAD OF HAVING THIS CALLBACK HERE (TO DO IN FUTURE ITERATIONS)
void Application::ProcessKeyboardInput()
{
	GLFWwindow* currentHandle = m_CurrentWindow->ReturnWindow();

    if (glfwGetKey(currentHandle, GLFW_KEY_W) == GLFW_PRESS)
        m_Camera->ProcessKeyboard(FORWARD, TimeManager::DeltaTime());
    if (glfwGetKey(currentHandle, GLFW_KEY_S) == GLFW_PRESS)
        m_Camera->ProcessKeyboard(BACKWARD, TimeManager::DeltaTime());
    if (glfwGetKey(currentHandle, GLFW_KEY_A) == GLFW_PRESS)
        m_Camera->ProcessKeyboard(LEFT, TimeManager::DeltaTime());
    if (glfwGetKey(currentHandle, GLFW_KEY_D) == GLFW_PRESS)
        m_Camera->ProcessKeyboard(RIGHT, TimeManager::DeltaTime());
}