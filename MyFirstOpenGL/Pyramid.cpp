#include "Pyramid.h"

void Pyramid::Update(float dt)
{
	// Apply velocity and rotation into forward direction
	transform.position = transform.position + transform.forward * velocity;
	transform.rotation = transform.rotation + glm::vec3(1.f, 0.f, 0.f) * angularVelocity + glm::vec3(0.f, 1.f, 0.f) * angularVelocity;

	// Invert forward when reached screen limits
	if (transform.position.y >= 0.4f || transform.position.y <= -0.4f) {
		transform.forward = transform.forward * -1.f;
	}

	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[1], "transform"), 1, GL_FALSE, glm::value_ptr(ApplyModelMatrix()));

}

glm::mat4 Pyramid::ApplyModelMatrix()
{
	// Create matrix that defines the translation and rotation
	glm::mat4 translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);
	glm::mat4 YrotationMatrix = MatrixUtilities::GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), transform.rotation.x);
	glm::mat4 XrotationMatrix = MatrixUtilities::GenerateRotationMatrix(glm::vec3(1.f, 0.f, 0.f), transform.rotation.x);

	return translationMatrix * XrotationMatrix * YrotationMatrix * glm::mat4(1.f);
}
