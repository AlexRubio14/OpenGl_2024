#include "GLManager.h"

void ResizeWindow(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight)
{
	//Definir nuevo tama�o del viewport
	glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);

	glUniform2f(glGetUniformLocation(SHADER_PROGRAM.compiledPrograms[0], "windowSize"), iFrameBufferWidth, iFrameBufferHeight);
}

void GLManager::WindowsConfiguration()
{
	//Inicializamos GLFW para gestionar ventanas e inputs
	glfwInit();

	//Configuramos la ventana
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Inicializamos la ventana
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Engine", NULL, NULL);

	//Asignamos funci�n de callback para cuando el frame buffer es modificado
	glfwSetFramebufferSizeCallback(window, ResizeWindow);

	//Definimos espacio de trabajo
	glfwMakeContextCurrent(window);
}

void GLManager::InitializeVaoAndVbo(GLuint& vao, GLuint& vbo, int numVaos, int numVbos)
{

	//Definimos cantidad de vao a crear y donde almacenarlos 
	glGenVertexArrays(numVaos, &vao);

	//Indico que el VAO activo de la GPU es el que acabo de crear
	glBindVertexArray(vao);

	//Definimos cantidad de vbo a crear y donde almacenarlos
	glGenBuffers(numVbos, &vbo);

	//Indico que el VBO activo es el que acabo de crear y que almacenar� un array. Todos los VBO que genere se asignaran al �ltimo VAO que he hecho glBindVertexArray
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void GLManager::ActivateFrontCulling()
{
	//Activamos cull face
	glEnable(GL_CULL_FACE);

	//Indicamos lado del culling
	glCullFace(GL_FRONT);
}

void GLManager::ActivateBackCulling()
{
	//Activamos cull face
	glEnable(GL_CULL_FACE);

	//Indicamos lado del culling
	glCullFace(GL_BACK);
}

void GLManager::VboConfiguration(GameObject* gameObject, int numVbo, int dimensions)
{
	//Ponemos los valores en el VBO creado
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * gameObject->GetVertexs().size(), gameObject->GetVertexs().data(), GL_STATIC_DRAW);

	//Indicamos donde almacenar y como esta distribuida la informaci�n
	glVertexAttribPointer(numVbo, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(GLfloat), (GLvoid*)0);

	//Indicamos que la tarjeta gr�fica puede usar el atributo 0
	glEnableVertexAttribArray(numVbo);

	//Desvinculamos VBO
	glBindBuffer(GL_ARRAY_BUFFER, numVbo);
}

void GLManager::VaoDesconfiguration(int numVao)
{
	//Desvinculamos VAO
	glBindVertexArray(numVao);
}
