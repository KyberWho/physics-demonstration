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
// APPLICATION CLASS
// -------------------------------------------------------------------------------

// Static member initialization (via 9.4.2 of C++ standard)
GLFWwindow* Application::m_CurrentWindow;

bool Application::m_RetrievedLibraries;

bool Application::m_AppRunning;
bool Application::m_InFullscreen;

// Initialises the window instance of the application
bool Application::CreateWindow()
{
    if (!glfwInit())
    {
        LOG_ERR("Failed to initialize GLFW\n");
        m_CurrentWindow = nullptr;

        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, OPENGL_DEBUG_MODE);

    m_CurrentWindow = glfwCreateWindow(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT, APP_NAME, NULL, NULL);
    m_InFullscreen = false;

    if (!m_CurrentWindow)
    {
		Application::Shutdown();
        return false;
    }

    glfwMakeContextCurrent(m_CurrentWindow);
	glfwSetFramebufferSizeCallback(m_CurrentWindow, FramebufferSizeCallback);

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

void Application::Shutdown()
{
    m_AppRunning = false;

    glfwDestroyWindow(m_CurrentWindow);
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

    while(!glfwWindowShouldClose(m_CurrentWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(m_CurrentWindow);
        glfwPollEvents();
    }

    Application::Shutdown();
}

void Application::SetFullscreen()
{
    GLFWmonitor* currentMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* currentMode = glfwGetVideoMode(currentMonitor);
    
    if (!m_InFullscreen)
    {
        m_InFullscreen = true;
        glfwSetWindowMonitor(m_CurrentWindow, currentMonitor, 0, 0, currentMode->width, 
            currentMode->height, currentMode->refreshRate);
    }
    else 
    {
        m_InFullscreen = false;
        glfwSetWindowMonitor(m_CurrentWindow, NULL, 0, 0, currentMode->width,
            currentMode->height, currentMode->refreshRate);
    }
}

// -------------------------------------------------------------------------------
// INPUT CLASS
// -------------------------------------------------------------------------------

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}
