#pragma once
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

	void Update(std::vector<GameObject*> _figures) {

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_SPACE) == GLFW_PRESS && !pauseKeyPressed) 
		{
			pauseKeyPressed = true;
			TIME_MANAGER.Pause();
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_M) == GLFW_PRESS && !keyMPressed && !TIME_MANAGER.GetPaused())
		{
			keyMPressed = true;
			GAMEOBJECT_MANAGER.AccelerateFigures();
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_N) == GLFW_PRESS && !keyNPressed && !TIME_MANAGER.GetPaused())
		{
			keyNPressed = true;
			GAMEOBJECT_MANAGER.DeccelerateFigures();
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_1) == GLFW_PRESS && !key1Pressed && !TIME_MANAGER.GetPaused())
		{
			key1Pressed = true;
			ChangePolygonMode();
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_2) == GLFW_PRESS && !key2Pressed && !TIME_MANAGER.GetPaused())
		{
			key2Pressed = true;
			SwitchActiveFigure(_figures[0]);
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_3) == GLFW_PRESS && !key3Pressed && !TIME_MANAGER.GetPaused())
		{
			key3Pressed = true;
			SwitchActiveFigure(_figures[1]);
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_4) == GLFW_PRESS && !key4Pressed && !TIME_MANAGER.GetPaused())
		{
			key4Pressed = true;
			SwitchActiveFigure(_figures[2]);
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_SPACE) == GLFW_RELEASE)
		{
			pauseKeyPressed = false;
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_M) == GLFW_RELEASE)
		{
			keyMPressed = false;
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_N) == GLFW_RELEASE)
		{
			keyNPressed = false;
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_SPACE) == GLFW_RELEASE)
		{
			pauseKeyPressed = false;
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_1) == GLFW_RELEASE)
		{
			key1Pressed = false;
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_2) == GLFW_RELEASE)
		{
			key2Pressed = false;
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_3) == GLFW_RELEASE)
		{
			key3Pressed = false;
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_4) == GLFW_RELEASE)
		{
			key4Pressed = false;
		}
	}

	void ChangePolygonMode() {

		if (polygonsAreFill) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			polygonsAreFill = false;
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			polygonsAreFill = true;
		}
	}

	void SwitchActiveFigure(GameObject* _figure) {
		_figure->SetIsActive(!_figure->GetIsActive());
	}
};