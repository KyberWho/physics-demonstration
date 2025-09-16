#include "Application.h"

// -------------------------------------------------------------------------------
// HELPER FUNCTIONS
// -------------------------------------------------------------------------------

// Callback function to adjust the viewport when the window is resized
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// -------------------------------------------------------------------------------
// APPLICATION CLASS
// -------------------------------------------------------------------------------

// Static member initialization (via 9.4.2 of C++ standard)
GLFWwindow* Application::m_CurrentWindow;

// Initialises the window instance of the application
bool Application::CreateWindow()
{
    if (!glfwInit())
    {
        LOG_ERR("Failed to initialize GLFW\n");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, OPENGL_DEBUG_MODE);

    m_CurrentWindow = glfwCreateWindow(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT, APP_NAME, NULL, NULL);
    if (!m_CurrentWindow)
    {
		Application::TerminateWindow();
        return false;
    }

    glfwMakeContextCurrent(m_CurrentWindow);
	glfwSetFramebufferSizeCallback(m_CurrentWindow, framebufferSizeCallback);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        LOG_ERR("Failed to initialize GLAD\n");
        return false;
	}

	LOG_INFO("OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << " has been loaded.");

    return true;
}

void Application::TerminateWindow()
{
    glfwTerminate();
}

// Main application loop (need to refactor this to separate event handling and rendering)
bool Application::UpdateWindow()
{
    while(!glfwWindowShouldClose(m_CurrentWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(m_CurrentWindow);
        glfwPollEvents();
    }

    return false; // When window is closed, return false
}