#include "TimeManager.h"

#include <GLFW/glfw3.h>

// -------------------------------------------------------------------------------
// TIME MANAGER CLASS
// -------------------------------------------------------------------------------

float TimeManager::m_DeltaTime = 0.0f;
float TimeManager::m_LastFrame = 0.0f;

// Updates the delta time by calculating the time difference between the current frame and the last frame
void TimeManager::Update()
{
	float currentFrame = (float) glfwGetTime();
	m_DeltaTime = currentFrame - m_LastFrame;
	m_LastFrame = currentFrame;
}

// Returns the delta time (time difference between the current frame and the last frame)
float TimeManager::DeltaTime()
{
	return m_DeltaTime;
}
