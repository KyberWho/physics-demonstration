// This module handles time management for the application, including calculating delta time and frame rate.
#pragma once

// -------------------------------------------------------------------------------
// TIME MANAGER CLASS
// -------------------------------------------------------------------------------

class TimeManager
{
private:
	static float m_DeltaTime;
	static float m_LastFrame;

public:
	static void Update();
	static float DeltaTime();
	static float FrameRate() { return 1.0f / m_DeltaTime; };
};