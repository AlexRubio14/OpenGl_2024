#include "TimeManager.h"

TimeManager::TimeManager() 
{
	//previousGameTime = (double)SDL_GetTicks() / 1000.0;
	deltaTime = 0.0f;
	FPS = 60;
	frameTime = 1.0f / (float)FPS;
	ShaderTimer = 0.f;
}

void TimeManager::Update()
{
	int currentTime = glfwGetTime();

	currentTime %= 6;

	ShaderTimer = currentTime;
}
