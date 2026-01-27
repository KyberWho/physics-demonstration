#include "TimeManager.h"

#include <GLFW/glfw3.h>

float TimeManager::m_DeltaTime = 0.0f;
float TimeManager::m_LastFrame = 0.0f;

void TimeManager::Update()
{
	float currentFrame = (float)glfwGetTime();
	m_DeltaTime = currentFrame - m_LastFrame;
	m_LastFrame = currentFrame;
}

float TimeManager::DeltaTime()
{
	return m_DeltaTime;
}
