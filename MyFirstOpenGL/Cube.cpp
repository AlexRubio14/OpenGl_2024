#include "Cube.h"
#include "GLManager.h"

Cube::Cube(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	: GameObject(_position, _rotation, _scale) {
	
	//Size (0.4 x 0.4 x 0.4)
	vertexs = {
		-0.2f, +0.2f, -0.2f, // 3
		+0.2f, +0.2f, -0.2f, // 2
		-0.2f, -0.2f, -0.2f, // 6
		+0.2f, -0.2f, -0.2f, // 7
		+0.2f, -0.2f, +0.2f, // 4
		+0.2f, +0.2f, -0.2f, // 2
		+0.2f, +0.2f, +0.2f, // 0
		-0.2f, +0.2f, -0.2f, // 3
		-0.2f, +0.2f, +0.2f, // 1
		-0.2f, -0.2f, -0.2f, // 6
		-0.2f, -0.2f, +0.2f, // 5
		+0.2f, -0.2f, +0.2f, // 4
		-0.2f, +0.2f, +0.2f, // 1
		+0.2f, +0.2f, +0.2f  // 0
	};

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
}

void Cube::Update(float _dt)
{
	// Apply velocity and rotation into forward direction
	transform.position = transform.position + (transform.forward * velocity) * _dt;
	transform.rotation = transform.rotation + (glm::vec3(0.f, 1.f, 0.f) * angularVelocity) * _dt;

	// Invert forward when reached screen limits
	if (transform.position.y >= 0.5f || transform.position.y <= -0.5f) {
		transform.forward = transform.forward * -1.f;
	}

	translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);
	rotationMatrix = MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.y);
	scaleMatrix = MatrixUtilities::GenerateScaleMatrix(transform.scale);

	//Genero la matriz vista
	glUseProgram(SHADERPROGRAM_MANAGER.compiledPrograms[0]);

	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[0], "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[0], "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[0], "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));
}

void Cube::Render()
{
	glUseProgram(SHADERPROGRAM_MANAGER.compiledPrograms[0]);
	InitProgramValues();
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, numVertexs);

	glBindVertexArray(0);
	glUseProgram(0);
}

void Cube::InitProgramValues()
{
	glUseProgram(SHADERPROGRAM_MANAGER.compiledPrograms[0]);
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[0], "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[0], "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[0], "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));

	glUniform2f(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[0], "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);
}
