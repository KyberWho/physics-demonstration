// This module handles the application lifecycle + any events: 
// e.g input polling, window resizing, etc.
#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Logger.h"
#include "Config.h"

// -------------------------------------------------------------------------------
// HELPER FUNCTIONS
// -------------------------------------------------------------------------------

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

// -------------------------------------------------------------------------------
// APPLICATION CLASS
// -------------------------------------------------------------------------------

// TODO: Separate window management into its individual components (keeping with single responsibility rule)?
// Class to handle everything to do with the application lifecycle
class Application
{
private:
	// The current window instance (only one window for now)
	static GLFWwindow* m_CurrentWindow;
public:
	Application() = delete; // Prevent instantiation of this class

	static bool CreateWindow();
	static void TerminateWindow();

	static bool UpdateWindow();
};