#include "TimeManager.h"

TimeManager::TimeManager() 
{
	FPS = 60;
	frameTime = 1.0f / (float)FPS;
	timeToReset = 6.f;

	paused = false;
}

void TimeManager::Update()
{
	if (!paused) {
		currentTime += frameTime;

		if (currentTime >= timeToReset)
		{
			currentTime -= timeToReset;
		}
	}
}
