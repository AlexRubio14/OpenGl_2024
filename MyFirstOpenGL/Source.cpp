#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#include "GLManager.h"
#include "ShaderProgram.h"
#include "GameObjectManager.h"

void main() {

	//Definir semillas del rand seg�n el tiempo
	srand(static_cast<unsigned int>(time(NULL)));

	GL_MANAGER.WindowsConfiguration(); 

	//Permitimos a GLEW usar funcionalidades experimentales
	glewExperimental = GL_TRUE;

	GL_MANAGER.ActivateBackCulling(); 

	//Inicializamos GLEW y controlamos errores
	if (glewInit() == GLEW_OK) {

		//Declarar instancia del gameObject
		GAMEOBJECT_MANAGER.CreateFigures(); 

		//Compilar shaders
		SHADER_PROGRAM.LoadVertexShader("MyFirstVertexShader.glsl");
		//SHADER_PROGRAM.LoadGeometryShader("MyFirstGeometryShader.glsl");
		SHADER_PROGRAM.LoadFragmentShader("FS_YellowOrange.glsl");

		//Compilar programa
		SHADER_PROGRAM.compiledPrograms.push_back(SHADER_PROGRAM.CreateProgram(SHADER_PROGRAM));

		//Definimos color para limpiar el buffer de color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Definimos modo de dibujo para cada cara
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		// CUBE VAO & VBO
		GLuint vaoCube, vboCube;

		GL_MANAGER.InitializeVaoAndVbo(vaoCube, vboCube, 1, 1);
		GL_MANAGER.VboConfiguration(GAMEOBJECT_MANAGER.gameObjects[0], 0);
		GL_MANAGER.VaoDesconfiguration(0);

		// PYRAMID VAO & VBO
		GLuint vaoPyramid, vboPyramid;

		GL_MANAGER.InitializeVaoAndVbo(vaoPyramid, vboPyramid, 1, 1);
		GL_MANAGER.VboConfiguration(GAMEOBJECT_MANAGER.gameObjects[1], 0);
		GL_MANAGER.VaoDesconfiguration(0);

		// ORTHOEDRON VAO & VBO
		GLuint vaoOrthohedron, vboOrthohedron;

		GL_MANAGER.InitializeVaoAndVbo(vaoOrthohedron, vboOrthohedron, 1, 1);
		GL_MANAGER.VboConfiguration(GAMEOBJECT_MANAGER.gameObjects[2], 0);
		GL_MANAGER.VaoDesconfiguration(0);

		//Indicar a la tarjeta GPU que programa debe usar
		glUseProgram(SHADER_PROGRAM.compiledPrograms[0]);

		//Asignar valores iniciales al programa
		glUniform2f(glGetUniformLocation(SHADER_PROGRAM.compiledPrograms[0], "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);

		//Generamos el game loop
		while (!glfwWindowShouldClose(GL_MANAGER.window)) {

			//Pulleamos los eventos (botones, teclas, mouse...)
			glfwPollEvents();

			//Limpiamos los buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			// CUBE UPDATE
			glBindVertexArray(vaoCube); //Definimos que queremos usar el VAO con los puntos
			GAMEOBJECT_MANAGER.gameObjects[0]->Update(0.f); // Aplico velocidad hacia el forward
			glUniformMatrix4fv(glGetUniformLocation(SHADER_PROGRAM.compiledPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(GAMEOBJECT_MANAGER.gameObjects[0]->ApplyModelMatrix())); //Aplicamos la matriz al shader
			glDrawArrays(GL_TRIANGLE_STRIP, 0, GAMEOBJECT_MANAGER.gameObjects[0]->NumTotalTriangles()); //Definimos que queremos dibujar
			glBindVertexArray(0); //Dejamos de usar el VAO indicado anteriormente

			// PYRAMID UPDATE
			//glUseProgram(compiledPrograms[1]);
			glBindVertexArray(vaoPyramid);
			GAMEOBJECT_MANAGER.gameObjects[1]->Update(0.f);
			glUniformMatrix4fv(glGetUniformLocation(SHADER_PROGRAM.compiledPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(GAMEOBJECT_MANAGER.gameObjects[1]->ApplyModelMatrix()));
			glDrawArrays(GL_TRIANGLE_STRIP, 0, GAMEOBJECT_MANAGER.gameObjects[1]->NumTotalTriangles());
			glBindVertexArray(0);

			// ORTHOHEDRON UPDATE
			//glUseProgram(compiledPrograms[2]);
			glBindVertexArray(vaoOrthohedron);
			GAMEOBJECT_MANAGER.gameObjects[2]->Update(0.f);
			glUniformMatrix4fv(glGetUniformLocation(SHADER_PROGRAM.compiledPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(GAMEOBJECT_MANAGER.gameObjects[2]->ApplyModelMatrix()));
			glDrawArrays(GL_TRIANGLE_STRIP, 0, GAMEOBJECT_MANAGER.gameObjects[2]->NumTotalTriangles());
			glBindVertexArray(0);

			//Cambiamos buffers
			glFlush();
			glfwSwapBuffers(GL_MANAGER.window);
		}

		//Desactivar y eliminar programa
		glUseProgram(0);
		glDeleteProgram(SHADER_PROGRAM.compiledPrograms[0]);

	}
	else {
		std::cout << "Ha petao." << std::endl;
		glfwTerminate();
	}

	//Finalizamos GLFW
	glfwTerminate();

}