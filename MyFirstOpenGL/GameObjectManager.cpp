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

void GameObjectManager::Draw(GLuint vaoCube, GLuint vaoOrthohedron, GLuint vaoPyramid)
{
	if (GAMEOBJECT_MANAGER.gameObjects[0]->GetIsActive()) {
		gameObjects[0]->Draw(vaoCube);
	}

	if (GAMEOBJECT_MANAGER.gameObjects[1]->GetIsActive()) {
		gameObjects[1]->Draw(vaoOrthohedron);
	}

	if (GAMEOBJECT_MANAGER.gameObjects[2]->GetIsActive()) {
		gameObjects[2]->Draw(vaoPyramid);
	}
}

