#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

#define TIME_MANAGER TimeManager::Instance()

class TimeManager {
private:

	TimeManager() = default;

	TimeManager(const TimeManager&) = delete;
	TimeManager& operator =(const TimeManager&) = delete;

public:

	inline static TimeManager& Instance()
	{
		static TimeManager timeManager;
		return timeManager;
	}

	float timer = 0;

	void Update() {
		
		int currentTime = glfwGetTime();

		currentTime %= 6;

		timer = currentTime;

		std::cout << timer << std::endl;
	};
};