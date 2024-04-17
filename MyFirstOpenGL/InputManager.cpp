#include "InputManager.h"

void InputManager::Update()
{
	if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_SPACE) == GLFW_PRESS && !pauseKeyPressed)
	{
		pauseKeyPressed = true;
		TIME_MANAGER.Pause();
	}

	if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_M) == GLFW_PRESS && !keyMPressed)
	{
		keyMPressed = true;
		TIME_MANAGER.AccelerateScaleTime();
	}

	if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_N) == GLFW_PRESS && !keyNPressed)
	{
		keyNPressed = true;
		TIME_MANAGER.DeclerateScaleTime();
	}

	if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_1) == GLFW_PRESS && !key1Pressed)
	{
		key1Pressed = true;
		ChangePolygonMode();
	}

	if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_2) == GLFW_PRESS && !key2Pressed)
	{
		key2Pressed = true;
		SwitchActiveFigure(GAMEOBJECT_MANAGER.gameObjects[0]);
	}

	if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_3) == GLFW_PRESS && !key3Pressed)
	{
		key3Pressed = true;
		SwitchActiveFigure(GAMEOBJECT_MANAGER.gameObjects[1]);
	}

	if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_4) == GLFW_PRESS && !key4Pressed)
	{
		key4Pressed = true;
		SwitchActiveFigure(GAMEOBJECT_MANAGER.gameObjects[2]);
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

void InputManager::ChangePolygonMode()
{
	if (polygonsAreFill) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		polygonsAreFill = false;
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		polygonsAreFill = true;
	}
}

void InputManager::SwitchActiveFigure(GameObject* _figure)
{
	_figure->SetIsActive(!_figure->GetIsActive());
}
