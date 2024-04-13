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

			if (!INPUT_MANAGER.GetPaused()) {

				if (GAMEOBJECT_MANAGER.gameObjects[0]->GetIsActive()) {
					// CUBE UPDATE
					glUseProgram(SHADERPROGRAM_MANAGER.compiledPrograms[0]); // Indicate to GPU wich programs has to use
					glBindVertexArray(vaoCube); // Define which VAO do we use 
					GAMEOBJECT_MANAGER.gameObjects[0]->Update(0.f); // Apply velocity into forward direction
					glDrawArrays(GL_TRIANGLE_STRIP, 0, GAMEOBJECT_MANAGER.gameObjects[0]->NumTotalTriangles()); //Define what we want to draw
					glBindVertexArray(0); // We desconfigurate the vao which we have used
				}

				if (GAMEOBJECT_MANAGER.gameObjects[1]->GetIsActive()) {
					// ORTHOHEDRON UPDATE
					glUseProgram(SHADERPROGRAM_MANAGER.compiledPrograms[0]);
					glBindVertexArray(vaoOrthohedron);
					GAMEOBJECT_MANAGER.gameObjects[1]->Update(0.f);
					glDrawArrays(GL_TRIANGLE_STRIP, 0, GAMEOBJECT_MANAGER.gameObjects[1]->NumTotalTriangles());
					glBindVertexArray(0);

					glUseProgram(0);
				}

				if (GAMEOBJECT_MANAGER.gameObjects[2]->GetIsActive()) {
					// PYRAMID UPDATE
					glUseProgram(SHADERPROGRAM_MANAGER.compiledPrograms[1]);
					glBindVertexArray(vaoPyramid);
					GAMEOBJECT_MANAGER.gameObjects[2]->Update(0.f);
					glUniform1f(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[1], "time"), TIME_MANAGER.GetShaderTimer());
					glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
					glDrawArrays(GL_TRIANGLE_STRIP, 6, 4);
					glBindVertexArray(0);
					glUseProgram(0);
				}
			}

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