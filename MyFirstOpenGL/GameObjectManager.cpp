#include "GameObjectManager.h"

GameObjectManager::~GameObjectManager()
{
	for (int i = 0; i < gameObjects.size(); i++) {
		delete gameObjects[i];
	}
}

void GameObjectManager::CreateFigures()
{
	gameObjects.push_back(new Cube(glm::vec3(-0.6f, 0.f, 0.f), glm::vec3(0), glm::vec3(1.f)));
	gameObjects.push_back(new Orthohedron(glm::vec3(0.f), glm::vec3(0.f, 0.f, 90.f), glm::vec3(1.f)));
	gameObjects.push_back(new Pyramid(glm::vec3(0.6f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(1.f)));
}
void GameObjectManager::AccelerateFigures()
{
	for (GameObject* gObj : gameObjects)
	{
		gObj->Accelerate();
	}
}

void GameObjectManager::DeccelerateFigures()
{
	for(GameObject* gObj : gameObjects)
	{
		gObj->Deccelerate();
	}
}

void GameObjectManager::Draw(std::vector<GLuint> _vaos)
{
	for (int i = 0; i < _vaos.size(); i++)
	{
		if (gameObjects[i]->GetIsActive()) 
		{
			gameObjects[i]->Draw(_vaos[i]);
		}
	}
}

