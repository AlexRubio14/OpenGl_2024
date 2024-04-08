#pragma once
#include <GL/glew.h>
#include "GameObject.h"

#define GLMANAGER GLManager::Instance()

static class GLManager {
private:

	GLManager() = default;

	GLManager(const GLManager&) = delete;
	GLManager& operator =(const GLManager&) = delete;

public:

	inline static GLManager& Instance()
	{
		static GLManager glManager;
		return glManager;
	}

	void InitializeVaoAndVbo(GLuint& vao, GLuint& vbo, const int numVaos, const int numVbos);

	void VboConfiguration(GameObject* gameObject, const int numVbo, const int dimensions = 3);

	void VaoDesconfiguration(const int numVao);
};
