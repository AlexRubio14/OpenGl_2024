#pragma once
#include <GLFW/glfw3.h>
#include "GLManager.h"

#define INPUT_MANAGER InputManager::Instance()

class InputManager
{
private:

	InputManager() { paused = false, polygonsAreFill = true; };

	InputManager(const InputManager&) = delete;
	InputManager& operator =(const InputManager&) = delete;

	bool paused;

	bool polygonsAreFill;

public:

	inline static InputManager& Instance()
	{
		static InputManager inputManager;
		return inputManager;
	}

	void Update(std::vector<GameObject*> figures) {

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_SPACE) == GLFW_PRESS) 
		{
			Pause();
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_M) == GLFW_PRESS)
		{
			AccelerateFIgures(figures);
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_N) == GLFW_PRESS)
		{
			DeccelerateFigures(figures);
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_1) == GLFW_PRESS)
		{
			ChangePolygonMode();
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_2) == GLFW_PRESS)
		{
			SwitchActiveFigure(figures[0]);
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_3) == GLFW_PRESS)
		{
			SwitchActiveFigure(figures[1]);
		}

		if (glfwGetKey(GL_MANAGER.window, GLFW_KEY_4) == GLFW_PRESS)
		{
			SwitchActiveFigure(figures[2]);
		}
	}

	void Pause() {
		paused != paused;
	}

	void AccelerateFIgures(std::vector<GameObject*> figures) {
		
		for (int i = 0; i < figures.size(); i++) {
			figures[i]->SetVelocity(figures[i]->GetVelocity() * 0.1f);
		}
	}

	void DeccelerateFigures(std::vector<GameObject*> figures) {

		for (int i = 0; i < figures.size(); i++) {
			figures[i]->SetVelocity((figures[i]->GetVelocity() * 0.1f) * -1);
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

	void SwitchActiveFigure(GameObject* figure) {
		figure->SetIsActive(!figure->GetIsActive());
	}

	inline bool GetPaused() const { return paused; }
};