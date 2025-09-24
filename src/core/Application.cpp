#include "Application.h"

// -------------------------------------------------------------------------------
// HELPER FUNCTIONS
// -------------------------------------------------------------------------------

// Callback function to adjust the viewport when the window is resized
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// -------------------------------------------------------------------------------
// WINDOW CLASS
// -------------------------------------------------------------------------------

Window::Window(int width, int height, const std::string& title)
    : m_WindowDimensions{width, height, 0, 0}, m_InFullscreen(false)
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

    if (!m_Handle)
    {
        LOG_ERR("Failed to create GLFW Window!");
        return;
    }

    glfwMakeContextCurrent(m_Handle);
    Init();
}

Window::~Window()
{
    if (m_Handle) glfwDestroyWindow(m_Handle);
}

void Window::Init() const
{
    glfwSetWindowSizeLimits(m_Handle, 640, 480, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetFramebufferSizeCallback(m_Handle, FramebufferSizeCallback);
}

GLFWwindow* Window::ReturnWindow() const { return m_Handle; }

void Window::SwapBuffers() const
{
    glfwSwapBuffers(m_Handle);
}

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

// -------------------------------------------------------------------------------
// APPLICATION CLASS
// -------------------------------------------------------------------------------

// Static member initialization (via 9.4.2 of C++ standard)

// Holds the current window of the application (only one for now)
Window* Application::m_CurrentWindow;

bool Application::m_RetrievedLibraries;

bool Application::m_AppRunning;
bool Application::m_InFullscreen;

// Initialises the window instance of the application
bool Application::CreateWindow()
{
    m_CurrentWindow = new Window(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT, APP_NAME);

    Application::InitialiseHandlers();

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        LOG_ERR("Failed to initialize GLAD\n");
        return false;
	}

	LOG_INFO("OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << " has been loaded.");

    m_AppRunning, m_RetrievedLibraries = true;

    return true;
}

// Initialises all handlers where necessary (e.g player controllers, camera controllers, etc.)
void Application::InitialiseHandlers()
{
    InputHandler::Init(m_CurrentWindow->ReturnWindow());
}

// Sets up default application actions (e.g fullscreen, unlock mouse, etc.)
void Application::RegisterApplicationActions()
{
    ActionHandler::CreateAction(GLFW_KEY_F11, &Window::SetFullscreen, m_CurrentWindow, "Toggle Fullscreen");
    InputHandler::AttachAction(ActionHandler::RetrieveAction("Toggle Fullscreen"), GLFW_PRESS);
}

// Terminates the program when called
void Application::Shutdown()
{
    m_AppRunning = false;
    InputHandler::ReleaseAllActions();
    ActionHandler::RemoveAllActions();

    delete m_CurrentWindow;
    glfwTerminate();
}

// Main application loop (need to refactor this to separate event handling and rendering)
void Application::Run()
{
    if (m_AppRunning) 
    {
        LOG_WARN("Application is already running!");
        return;
    }

    Application::RegisterApplicationActions();

    while(!m_CurrentWindow->ShouldClose())
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        m_CurrentWindow->SwapBuffers();
        m_CurrentWindow->PollEvents();
    }
    
    Application::Shutdown();
}