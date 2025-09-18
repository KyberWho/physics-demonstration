// This module handles the application lifecycle + any events: 
// e.g input polling, window resizing, etc.
#pragma once

// -------------------------------------------------------------------------------
// HEADER FILES/DEPENDENCIES
// -------------------------------------------------------------------------------
#include <vector>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Config.h"
#include "Logger.h"
#include "TimeManager.h"

// -------------------------------------------------------------------------------
// HELPER FUNCTIONS
// -------------------------------------------------------------------------------

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

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
	
	static bool m_RetrievedLibraries;
	
	static bool m_AppRunning;
	static bool m_InFullscreen;

public:
	// Prevents instantiation of this class
	Application() = delete;
	static bool CreateWindow();

	static void Run();
	static void Shutdown();

	static void SetFullscreen();
};

// -------------------------------------------------------------------------------
// INPUT CLASS
// -------------------------------------------------------------------------------

enum Action
{
	PRESS = GLFW_PRESS,
	HELD = GLFW_REPEAT,
	RELEASE = GLFW_RELEASE
};

struct KeyState
{
	int m_Key;
	Action m_currentAction;
};

// TODO: Need to implement methods that are generic and work with every possible key + combinations
class InputHandler
{
private:
	// static std::vector<KeyState> m_Keys;
	// append keys that are currently being used 
	static bool m_Keys[GLFW_KEY_LAST];
	static bool m_KeysPressed[GLFW_KEY_LAST];
	static bool m_KeysReleased[GLFW_KEY_LAST];
public:
	InputHandler() = delete;

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};