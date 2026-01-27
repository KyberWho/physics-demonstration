#pragma once

class TimeManager
{
private:
	static float m_DeltaTime;
	static float m_LastFrame;

public:
	static void Update();
	static float DeltaTime();
};