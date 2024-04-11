#include "GameObjectManager.h"

void GameObjectManager::CreateFigures()
{
	gameObjects.push_back(new Cube(glm::vec3(-0.6f, 0.f, 0.f), glm::vec3(0), glm::vec3(1.f)));
	gameObjects.push_back(new Orthohedron(glm::vec3(0.f), glm::vec3(0.f, 0.f, 90.f), glm::vec3(1.f)));
	gameObjects.push_back(new Pyramid(glm::vec3(0.6f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(1.f)));
}; 
