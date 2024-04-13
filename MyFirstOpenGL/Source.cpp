#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#include "GLManager.h"
#include "ShaderProgramManager.h"
#include "GameObjectManager.h"
#include "TimeManager.h"
#include "InputManager.h"

void main() {

	srand(static_cast<unsigned int>(time(NULL)));

	GL_MANAGER.WindowsConfiguration(); 

	// Give GLEW permission to use experimental functionalities
	glewExperimental = GL_TRUE;

	GL_MANAGER.ActivateBackCulling(); 

	// Initialize GLEW and control errors Inicializamos GLEW y controlamos errores
	if (glewInit() == GLEW_OK) {

		GAMEOBJECT_MANAGER.CreateFigures(); 

		// Define wich color we use for cleaning buffer
		glClearColor(0.f, 0.f, 0.f, 1.f);

		// Define draw mode to -> face to face
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		//TODO Convert into a single vao & vbo
		/*GLuint vaoFigures, vboFigures;
		GL_MANAGER.InitializeVaoAndVbo(vaoFigures, vboFigures, 3, 3);*/

		// CUBE VAO & VBO
		GLuint vaoCube, vboCube;

		GL_MANAGER.InitializeVaoAndVbo(vaoCube, vboCube, 1, 1);
		GL_MANAGER.VboConfiguration(GAMEOBJECT_MANAGER.gameObjects[0], 0);
		GL_MANAGER.VaoDesconfiguration(0);

		// ORTHOEDRON VAO & VBO
		GLuint vaoOrthohedron, vboOrthohedron;

		GL_MANAGER.InitializeVaoAndVbo(vaoOrthohedron, vboOrthohedron, 1, 1);
		GL_MANAGER.VboConfiguration(GAMEOBJECT_MANAGER.gameObjects[1], 0);
		GL_MANAGER.VaoDesconfiguration(0);

		// PYRAMID VAO & VBO
		GLuint vaoPyramid, vboPyramid;

		GL_MANAGER.InitializeVaoAndVbo(vaoPyramid, vboPyramid, 1, 1);
		GL_MANAGER.VboConfiguration(GAMEOBJECT_MANAGER.gameObjects[2], 0);
		GL_MANAGER.VaoDesconfiguration(0);

		glUseProgram(SHADERPROGRAM_MANAGER.compiledPrograms[0]);
		glUniform2f(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[0], "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);

		//Assign initial values to programs
		glUseProgram(SHADERPROGRAM_MANAGER.compiledPrograms[1]);
		glUniform2f(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[1], "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);
		glUniform1f(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[1], "time"), TIME_MANAGER.GetShaderTimer());

		//Generate game loop
		while (!glfwWindowShouldClose(GL_MANAGER.window)) {

			//Pull events (buttons, keys, mouse...)
			glfwPollEvents();

			//Clean buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			INPUT_MANAGER.Update(GAMEOBJECT_MANAGER.gameObjects);
			TIME_MANAGER.Update();

			GAMEOBJECT_MANAGER.Draw(vaoCube, vaoOrthohedron, vaoPyramid);

			//Switch buffers
			glFlush();
			glfwSwapBuffers(GL_MANAGER.window);
		}

		//Deactive & delete program
		glUseProgram(0);
		SHADERPROGRAM_MANAGER.DeletePrograms();
	}
	else {
		std::cout << "Program Crashes" << std::endl;
		glfwTerminate();
	}

	//Finish GLFW
	glfwTerminate();

}