#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#include "Cube.h"
#include "Orthohedron.h"
#include "Pyramid.h"
#include "GLManager.h"
#include "ShaderProgram.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

std::vector<GLuint> compiledPrograms;

void Resize_Window(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight) {

	//Definir nuevo tamaño del viewport
	glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);

	glUniform2f(glGetUniformLocation(compiledPrograms[0], "windowSize"), iFrameBufferWidth, iFrameBufferHeight);
}

void main() {

	//Definir semillas del rand según el tiempo
	srand(static_cast<unsigned int>(time(NULL)));

	//Inicializamos GLFW para gestionar ventanas e inputs
	glfwInit();

	//Configuramos la ventana
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Inicializamos la ventana
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Engine", NULL, NULL);

	//Asignamos función de callback para cuando el frame buffer es modificado
	glfwSetFramebufferSizeCallback(window, Resize_Window);

	//Definimos espacio de trabajo
	glfwMakeContextCurrent(window);

	//Permitimos a GLEW usar funcionalidades experimentales
	glewExperimental = GL_TRUE;

	//Activamos cull face
	glEnable(GL_CULL_FACE);

	//Indicamos lado del culling
	glCullFace(GL_BACK);

	//Inicializamos GLEW y controlamos errores
	if (glewInit() == GLEW_OK) {

		//Declarar instancia del gameObject
		GameObject* cube = new Cube(glm::vec3(-0.6f, 0.f, 0.f), glm::vec3(0), glm::vec3(0));
		GameObject* orthohedron = new Orthohedron(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0), glm::vec3(0));
		GameObject* pyramid = new Pyramid(glm::vec3(0.6f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f));

		//Compilar shaders
		ShaderProgram myFirstProgram;
		myFirstProgram.LoadVertexShader("MyFirstVertexShader.glsl");
		//myFirstProgram.LoadGeometryShader("MyFirstGeometryShader.glsl");
		myFirstProgram.LoadFragmentShader("MyFirstFragmentShader.glsl");

		//Compilar programa
		compiledPrograms.push_back(myFirstProgram.CreateProgram(myFirstProgram));

		//Definimos color para limpiar el buffer de color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Definimos modo de dibujo para cada cara
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		// CUBE VAO & VBO
		GLuint vaoCube, vboCube;

		GLMANAGER.InitializeVaoAndVbo(vaoCube, vboCube, 1, 1);
		GLMANAGER.VboConfiguration(cube, 0);
		GLMANAGER.VaoDesconfiguration(0);

		// PYRAMID VAO & VBO
		GLuint vaoPyramid, vboPyramid;

		GLMANAGER.InitializeVaoAndVbo(vaoPyramid, vboPyramid, 1, 1);
		GLMANAGER.VboConfiguration(pyramid, 0);
		GLMANAGER.VaoDesconfiguration(0);

		// ORTHOEDRON VAO & VBO
		GLuint vaoOrthohedron, vboOrthohedron;

		GLMANAGER.InitializeVaoAndVbo(vaoOrthohedron, vboOrthohedron, 1, 1);
		GLMANAGER.VboConfiguration(orthohedron, 0);
		GLMANAGER.VaoDesconfiguration(0);

		////Indicar a la tarjeta GPU que programa debe usar
		glUseProgram(compiledPrograms[0]);

		//Asignar valores iniciales al programa
		glUniform2f(glGetUniformLocation(compiledPrograms[0], "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);
		//glUniformMatrix4fv(glGetUniformLocation(compiledPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

		//Generamos el game loop
		while (!glfwWindowShouldClose(window)) {

			//Pulleamos los eventos (botones, teclas, mouse...)
			glfwPollEvents();

			//Limpiamos los buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			// CUBE UPDATE
			glUseProgram(compiledPrograms[0]);
			glBindVertexArray(vaoCube); //Definimos que queremos usar el VAO con los puntos
			cube->Update(0.f); // Aplico velocidad hacia el forward
			glUniformMatrix4fv(glGetUniformLocation(compiledPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(cube->ApplyModelMatrix())); //Aplicamos la matriz al shader
			glDrawArrays(GL_TRIANGLE_STRIP, 0, cube->NumTotalTriangles()); //Definimos que queremos dibujar
			glBindVertexArray(0); //Dejamos de usar el VAO indicado anteriormente

			// PYRAMID UPDATE
			//glUseProgram(compiledPrograms[1]);
			glBindVertexArray(vaoPyramid);
			pyramid->Update(0.f); 
			glUniformMatrix4fv(glGetUniformLocation(compiledPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(pyramid->ApplyModelMatrix()));
			glDrawArrays(GL_TRIANGLE_STRIP, 0, pyramid->NumTotalTriangles());
			glBindVertexArray(0);

			// ORTHOHEDRON UPDATE
			//glUseProgram(compiledPrograms[2]);
			glBindVertexArray(vaoOrthohedron);
			orthohedron->Update(0.f);
			glUniformMatrix4fv(glGetUniformLocation(compiledPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(orthohedron->ApplyModelMatrix()));
			glDrawArrays(GL_TRIANGLE_STRIP, 0, orthohedron->NumTotalTriangles());
			glBindVertexArray(0);

			//Cambiamos buffers
			glFlush();
			glfwSwapBuffers(window);
		}

		//Desactivar y eliminar programa
		glUseProgram(0);
		glDeleteProgram(compiledPrograms[0]);

	}
	else {
		std::cout << "Ha petao." << std::endl;
		glfwTerminate();
	}

	//Finalizamos GLFW
	glfwTerminate();

}