#pragma once
#include "Cube.h"
#include "Orthohedron.h"
#include "Pyramid.h"
#include "TimeManager.h"
#include "GLManager.h"

#define GAMEOBJECT_MANAGER GameObjectManager::Instance()

class GameObjectManager
{
private:

	GameObjectManager() = default;


	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager& operator =(const GameObjectManager&) = delete;

public:

	inline static GameObjectManager& Instance()
	{
		static GameObjectManager gameObjectManager;
		return gameObjectManager;
	}

	~GameObjectManager();

	std::vector<GameObject*> gameObjects;

	void CreateFigures();

	void AccelerateFigures();
	void DeccelerateFigures();

	void Draw(GLuint vaoCube, GLuint vaoOrthohedron, GLuint vaoPyramid);
};