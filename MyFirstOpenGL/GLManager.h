#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ShaderProgramManager.h"
#include "GameObject.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define GL_MANAGER GLManager::Instance()

class GLManager {
private:

	GLManager();

	GLManager(const GLManager&) = delete;
	GLManager& operator =(const GLManager&) = delete;

public:

	inline static GLManager& Instance()
	{
		static GLManager glManager;
		return glManager;
	}

	GLFWwindow* window;

	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;
	
	void WindowsConfiguration();

	void ActivateFrontCulling();
	void ActivateBackCulling();

	void InitializeVaoAndVbo(GLuint& _vao, GLuint& _vbo, const int _numVaos, const int _numVbos);

	void VboConfiguration(GameObject* _gameObject, const int _numVbo, const int _dimensions = 3);

	void VaoDesconfiguration(const int _numVao);

	void SetUpVaosAndVbos();
};

void ResizeWindow(GLFWwindow* _window, int _iFrameBufferWidth, int _iFrameBufferHeight); 