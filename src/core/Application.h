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

static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

// -------------------------------------------------------------------------------
// WINDOW CLASS
// -------------------------------------------------------------------------------

class Window
{
private:
	GLFWwindow* m_Handle;

	int m_WindowDimensions[4]; // Width, Height, XPos, YPos
	bool m_InFullscreen;
public:
	Window(int width, int height, const std::string& title);
	~Window();
	
	void Init() const;

	GLFWwindow* ReturnWindow() const;

	void SwapBuffers() const;
	void PollEvents() const;

	bool ShouldClose() const;

	void SetFullscreen();
};

// -------------------------------------------------------------------------------
// APPLICATION CLASS
// -------------------------------------------------------------------------------

// TODO: Add application info class which keeps all the information secure

// Class to handle everything to do with the application lifecycle
class Application
{
private:
	static Window* m_CurrentWindow;

	static bool m_RetrievedLibraries;
	
	static bool m_AppRunning;
	static bool m_InFullscreen;

public:
	Application() = delete;
	static bool CreateWindow();
	static void InitialiseHandlers();

	static void RegisterApplicationActions();

	static void Run();
	static void Shutdown();
};