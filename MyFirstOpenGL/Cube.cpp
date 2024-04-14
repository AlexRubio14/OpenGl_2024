#include "Cube.h"


void Cube::Update(float _dt)
{
	// Apply velocity and rotation into forward direction
	transform.position = transform.position + transform.forward * velocity;
	transform.rotation = transform.rotation + glm::vec3(0.f, 1.f, 0.f) * angularVelocity;

	// Invert forward when reached screen limits
	if (transform.position.y >= 0.5f || transform.position.y <= -0.5f) {
		transform.forward = transform.forward * -1.f;
	}

	modelMatrix = ApplyModelMatrix();
}

void Cube::Draw(GLuint _vao)
{
	glUseProgram(SHADERPROGRAM_MANAGER.compiledPrograms[0]);
	glBindVertexArray(_vao);

	if (!TIME_MANAGER.GetPaused()) {
		Update(0.f);
	}

	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(modelMatrix)); //Aplicamos la matriz al shader


	glDrawArrays(GL_TRIANGLE_STRIP, 0, NumTotalTriangles());
	glBindVertexArray(0);
}

glm::mat4 Cube::ApplyModelMatrix()
{
	// Create matrix that defines the translation and rotation 
	glm::mat4 translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);
	glm::mat4 rotationMatrix = MatrixUtilities::GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), transform.rotation.y);

	return translationMatrix * rotationMatrix * glm::mat4(1.f);
}
