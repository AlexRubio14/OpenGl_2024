#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

#define TIME_MANAGER TimeManager::Instance()

class TimeManager {
private:

	float deltaTime;
	int FPS;
	float frameTime;
	float previousGameTime;

	float ShaderTimer;

	TimeManager();	

	TimeManager(const TimeManager&) = delete;
	TimeManager& operator =(const TimeManager&) = delete;

public:

	inline static TimeManager& Instance()
	{
		static TimeManager timeManager;
		return timeManager;
	}

	void Update();

	inline float GetShaderTimer() const { return ShaderTimer; }
};