#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"
#include "GameObject.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define GL_MANAGER GLManager::Instance()

class GLManager {
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

	GLFWwindow* window;
	
	void WindowsConfiguration();

	void ActivateFrontCulling();
	void ActivateBackCulling();

	void InitializeVaoAndVbo(GLuint& vao, GLuint& vbo, const int numVaos, const int numVbos);

	void VboConfiguration(GameObject* gameObject, const int numVbo, const int dimensions = 3);

	void VaoDesconfiguration(const int numVao);
};

void ResizeWindow(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight); 