#include "Pyramid.h"
#include "TimeManager.h"
#include "GLManager.h"

Pyramid::Pyramid(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	: GameObject(_position, _rotation, _scale) {

		//Size (0.4 x 0.6 x 0.4)
		vertexs = {
				+0.0f, +0.5f, +0.0f,
				-0.2f, -0.5f, +0.2f,
				+0.2f, -0.5f, +0.2f,
				+0.2f, -0.5f, -0.2f,
				-0.2f, -0.5f, -0.2f,
				-0.2f, -0.5f, +0.2f,

				// Triangle Strip
				+0.2f, -0.5f, +0.2f,
				-0.2f, -0.5f, +0.2f,
				+0.2f, -0.5f, -0.2f,
				-0.2f, -0.5f, -0.2f,
		};

		// Assing num of vertex
		numVertexs = vertexs.size() / 3;

		// Generate VAO/VBO
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);


		// Define active VAO
		glBindVertexArray(VAO);

		// Define positions VBO as active
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexs.size() * sizeof(float), vertexs.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		// Active the attribute 0
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	};

void Pyramid::Update(float _dt)
{
	// Apply velocity and rotation into forward direction
	transform.position = transform.position + transform.forward * velocity * _dt;
	transform.rotation = transform.rotation + ((glm::vec3(1.f, 0.f, 0.f) * angularVelocity + glm::vec3(0.f, 1.f, 0.f) * angularVelocity) * _dt);

	// Invert forward when reached screen limits
	if (transform.position.y >= 0.4f || transform.position.y <= -0.4f) {
		transform.forward = transform.forward * -1.f;
	}

	translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);
	rotationMatrix = MatrixUtilities::GenerateRotationMatrix(glm::vec3(1.f, 0.f, 0.f), transform.rotation.x);
	rotationMatrixY = MatrixUtilities::GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), transform.rotation.y);
	scaleMatrix = MatrixUtilities::GenerateScaleMatrix(transform.scale);

	glUseProgram(SHADERPROGRAM_MANAGER.compiledPrograms[2]);

	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[2], "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[2], "rotationMatrixX"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[2], "rotationMatrixY"), 1, GL_FALSE, glm::value_ptr(rotationMatrixY));
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[2], "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));
}

void Pyramid::Render()
{
	// PYRAMID UPDATE
	glUseProgram(SHADERPROGRAM_MANAGER.compiledPrograms[2]);
	glBindVertexArray(VAO);

	glUniform1f(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[2], "time"), TIME_MANAGER.GetCurrentTime());
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
	glDrawArrays(GL_TRIANGLE_STRIP, 6, 4);

	glBindVertexArray(0);
}

void Pyramid::InitProgramValues()
{
	glUseProgram(SHADERPROGRAM_MANAGER.compiledPrograms[2]);
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[2], "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[2], "rotationMatrixX"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[2], "rotationMatrixY"), 1, GL_FALSE, glm::value_ptr(rotationMatrixY));
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[2], "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));

	glUniform2f(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[2], "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);
	glUniform1f(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[2], "time"), TIME_MANAGER.GetCurrentTime());
}
