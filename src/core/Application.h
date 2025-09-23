// This module handles the application lifecycle + any events: 
// e.g input polling, window resizing, etc.
#pragma once

// -------------------------------------------------------------------------------
// HEADER FILES/DEPENDENCIES
// -------------------------------------------------------------------------------

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Config.h"
#include "Input.h"
#include "Logger.h"
#include "TimeManager.h"

// -------------------------------------------------------------------------------
// HELPER FUNCTIONS
// -------------------------------------------------------------------------------

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

// -------------------------------------------------------------------------------
// APPLICATION CLASS
// -------------------------------------------------------------------------------

// TODO: Separate application management into a window class (keeping with single responsibility rule)?
// Maybe also add application info class which keeps all the information secure

// Class to handle everything to do with the application lifecycle
class Application
{
private:
	// The current window instance (only one window for now)
	static GLFWwindow* m_CurrentWindow;
	
	static bool m_RetrievedLibraries;
	
	static bool m_AppRunning;
	static bool m_InFullscreen;

public:
	Application() = delete;
	static bool CreateWindow();

	static void Run();
	static void Shutdown();

	static void SetFullscreen();
};