#include "Cube.h"

void Cube::Update(float dt)
{
	// Apply velocity and rotation into forward direction
	transform.position = transform.position + transform.forward * velocity;
	transform.rotation = transform.rotation + glm::vec3(0.f, 1.f, 0.f) * angularVelocity;

	// Invert forward when reached screen limits
	if (transform.position.y >= 0.5f || transform.position.y <= -0.5f) {
		transform.forward = transform.forward * -1.f;
	}

	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(ApplyModelMatrix())); //Aplicamos la matriz al shader
}

glm::mat4 Cube::ApplyModelMatrix()
{
	// Create matrix that defines the translation and rotation 
	glm::mat4 translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);
	glm::mat4 rotationMatrix = MatrixUtilities::GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), transform.rotation.y);

	return translationMatrix * rotationMatrix * glm::mat4(1.f);
}
