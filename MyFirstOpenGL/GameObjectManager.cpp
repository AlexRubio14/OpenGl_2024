#include "GameObjectManager.h"

GameObjectManager::~GameObjectManager()
{
	for (GameObject* gObj : gameObjects)
	{
		delete gObj;
	}
}

void GameObjectManager::CreateFigures()
{
	gameObjects.push_back(new Cube(glm::vec3(-0.6f, 0.f, 0.f), glm::vec3(0), glm::vec3(1.f)));
	gameObjects.push_back(new Orthohedron(glm::vec3(0.f), glm::vec3(0.f, 0.f, 90.f), glm::vec3(1.f)));
	gameObjects.push_back(new Pyramid(glm::vec3(0.6f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(1.f)));
}

void GameObjectManager::Update(float _dt)
{
	for (GameObject* gObj : gameObjects) {
		gObj->Update(_dt);
	}
}

void GameObjectManager::Render()
{
	for (GameObject* gObj : gameObjects)
	{
		if (gObj->GetIsActive())
		{
			gObj->Render();
		}
	}
}

void GameObjectManager::InitProgramsValues()
{
	for (GameObject* gObj : gameObjects)
		gObj->InitProgramValues();
}

