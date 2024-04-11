#include "Orthohedron.h"
#include <iostream>

void Orthohedron::Update(float dt)
{
	// Apply rotation into forward direction
	transform.rotation = transform.rotation + glm::vec3(0.f, 0.f, 1.f) * angularVelocity;

	if (transform.scale.y <= 0.3f)
		transform.scaleVelocity = 0.01f;
	else if (transform.scale.y >= 0.7f)
		transform.scaleVelocity = -0.01f;

	transform.scale.y += transform.scaleVelocity;
}

glm::mat4 Orthohedron::ApplyModelMatrix()
{
	// Create matrix that defines the translation and rotation
	glm::mat4 rotationMatrix = MatrixUtilities::GenerateRotationMatrix(glm::vec3(0.f, 0.f, 1.f), transform.rotation.z);

	glm::mat4 scaleMatrix = MatrixUtilities::GenerateScaleMatrix(transform.scale);

	return rotationMatrix * scaleMatrix * glm::mat4(1.f);
}
