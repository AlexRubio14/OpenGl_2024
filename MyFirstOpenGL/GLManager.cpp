#include "GLManager.h"
#include "GameObjectManager.h"

GLManager::GLManager() {

	// CUBE VAO & VBO
	GLuint vaoCube, vboCube;
	// ORTHOEDRON VAO & VBO
	GLuint vaoOrthohedron, vboOrthohedron;
	// PYRAMID VAO & VBO
	GLuint vaoPyramid, vboPyramid;

	vaos.push_back(vaoCube);
	vaos.push_back(vaoOrthohedron);
	vaos.push_back(vaoPyramid);

	vbos.push_back(vboCube);
	vbos.push_back(vboOrthohedron);
	vbos.push_back(vboPyramid);
}

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

void GLManager::InitializeVaoAndVbo(GLuint& _vao, GLuint& _vbo, int _numVaos, int _numVbos)
{

	// Define how many vaos do we have to create and where allocate them
	glGenVertexArrays(_numVaos, &_vao);

	// Indicate the active vao in GPU
	glBindVertexArray(_vao);

	// Define how many Vbo do we create and where allocate them
	glGenBuffers(_numVbos, &_vbo);

	// Indicate the active vbo and the memory allocated will be an array. Every vbo generated will be assigned in the last Vao binded.
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
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

void GLManager::VboConfiguration(GameObject* _gameObject, int _numVbo, int _dimensions)
{
	// Set the values into created VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _gameObject->GetVertexs().size(), _gameObject->GetVertexs().data(), GL_STATIC_DRAW);

	// Indicate the place to allocate memory and how will be info distributed
	glVertexAttribPointer(_numVbo, _dimensions, GL_FLOAT, GL_FALSE, _dimensions * sizeof(GLfloat), (GLvoid*)0);

	// Indicate to GPU can use the attribute X 
	glEnableVertexAttribArray(_numVbo);

	// Unlink VBO
	glBindBuffer(GL_ARRAY_BUFFER, _numVbo);
}

void GLManager::VaoDesconfiguration(int _numVao)
{
	// Unlink VAO
	glBindVertexArray(_numVao);
}

void GLManager::SetUpVaosAndVbos()
{

	for (int i = 0; i < vaos.size(); i++) {

		GL_MANAGER.InitializeVaoAndVbo(vaos[i], vbos[i], 1, 1);
		GL_MANAGER.VboConfiguration(GAMEOBJECT_MANAGER.gameObjects[i], 0);
		GL_MANAGER.VaoDesconfiguration(0);
	}
}

void ResizeWindow(GLFWwindow* _window, int _iFrameBufferWidth, int _iFrameBufferHeight)
{
	// Define new viewport size
	glViewport(0, 0, _iFrameBufferWidth, _iFrameBufferHeight);

	glUniform2f(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[0], "windowSize"), _iFrameBufferWidth, _iFrameBufferHeight);
}