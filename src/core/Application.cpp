#include "Application.h"

// Static member initialization (via 9.4.2 of C++ standard)
GLFWwindow* Application::m_CurrentWindow;

// Initialises the window instance of the application
bool Application::CreateWindow()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    m_CurrentWindow = glfwCreateWindow(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT, APP_NAME, NULL, NULL);
    if (!m_CurrentWindow)
    {
		Application::TerminateWindow();
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_CurrentWindow);

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