#include "GLManager.h"
#include "GameObjectManager.h"

void GLManager::WindowsConfiguration()
{
	// iNITIALIZE glfw to manage window & inputs
	glfwInit();

	// Configurate the windows
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Initialize the window
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Engine", NULL, NULL);

	// Assign callback function everytime frame buffer is modificated 	
	glfwSetFramebufferSizeCallback(window, ResizeWindow);

	// Define workspace
	glfwMakeContextCurrent(window);
}

void GLManager::ActivateFrontCulling()
{
	// Activate cull face 
	glEnable(GL_CULL_FACE);

	// Indicate side of culling
	glCullFace(GL_FRONT);
}

void GLManager::ActivateBackCulling()
{
	// Activate cull face 
	glEnable(GL_CULL_FACE);

	// Indicate side of culling
	glCullFace(GL_BACK);
}

void ResizeWindow(GLFWwindow* _window, int _iFrameBufferWidth, int _iFrameBufferHeight)
{
	// Define new viewport size
	glViewport(0, 0, _iFrameBufferWidth, _iFrameBufferHeight);

	glUniform2f(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[0], "windowSize"), _iFrameBufferWidth, _iFrameBufferHeight);
}