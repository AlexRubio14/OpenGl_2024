#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLManager.h"
#include "GameObjectManager.h"

#define INPUT_MANAGER InputManager::Instance()

class InputManager
{
private:

	InputManager()
		: polygonsAreFill(true), pauseKeyPressed(false), key1Pressed(false), 
		  key2Pressed(false), key3Pressed(false), key4Pressed(false), keyMPressed(false), keyNPressed(false) {};

	InputManager(const InputManager&) = delete;
	InputManager& operator =(const InputManager&) = delete;

	bool pauseKeyPressed;

	bool keyMPressed;
	bool keyNPressed;

	bool key1Pressed;
	bool key2Pressed;
	bool key3Pressed;
	bool key4Pressed;

	bool polygonsAreFill;

public:

	inline static InputManager& Instance()
	{
		static InputManager inputManager;
		return inputManager;
	}

	void Update();

	void ChangePolygonMode();

	void SwitchActiveFigure(GameObject* _figure);
};