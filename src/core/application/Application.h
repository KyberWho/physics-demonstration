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
#include "TimeManager.h"

#include "Camera.h"
#include "Renderer.h"

#include "Box.h"
#include "PhysicsEngine.h"

#include "Entity.h"

#include "Logger.h"

// -------------------------------------------------------------------------------
// PREPROCESSOR DEFINITIONS
// -------------------------------------------------------------------------------

#define MAX_GRID_SIZE 3
#define MAX_ENTITIES (MAX_GRID_SIZE * MAX_GRID_SIZE)

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

	int m_WindowDimensions[4]; // Width, Height, XPos, YPos (in framebuffer sizes)
	unsigned int m_ScreenDimensions[2]; // Width, Height (in screen sizes)

	bool m_InFullscreen = false;
	bool m_MouseLocked = false;
public:
	Window(int width, int height, const std::string& title);
	~Window();
	
	void Init() const;

	GLFWwindow* ReturnWindow() const;

	void SwapBuffers() const;
	void PollEvents() const;

	bool ShouldClose() const;

	void SetFullscreen();
	void ChangeMouseLock();

	bool IsMouseLocked() const { return m_MouseLocked; }

	void SetScreenWidth(unsigned int currentWidth) { m_ScreenDimensions[0] = currentWidth; }
	void SetScreenHeight(unsigned int currentHeight) { m_ScreenDimensions[1] = currentHeight; }
	unsigned int GetScreenWidth() const { return m_ScreenDimensions[0]; }
	unsigned int GetScreenHeight() const { return m_ScreenDimensions[1]; }
};

// -------------------------------------------------------------------------------
// APPLICATION CLASS
// -------------------------------------------------------------------------------

// TODO: Add application info class which keeps all the information secure (for future iterations only)

// Class to handle everything to do with the application lifecycle
class Application
{
private:
	static Window* m_CurrentWindow;
	static Camera* m_Camera;
	
	static TextureRenderer* m_TextureRenderer;
	static MeshRenderer* m_MeshRenderer;

	static bool m_FirstMouse;
	static float m_LastX;
	static float m_LastY;

	static bool m_RetrievedLibraries;
	static bool m_AppRunning;

public:
	Application() = delete;
	static bool CreateWindow();
	static void InitialiseHandlers();

	static void RegisterApplicationActions();

	static void Run();
	static void Shutdown();

	static void EnableFreeMouseMovement(double xPos, double yPos);

	// REFACTOR THIS TO WORK WITH INPUT HANDLER INSTEAD OF HAVING THESE CALLBACKS HERE (TO DO IN FUTURE ITERATIONS)
	static void ProcessMouseInput(float xpos, float ypos);
	static void ProcessKeyboardInput();
};