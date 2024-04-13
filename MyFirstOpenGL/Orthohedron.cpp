#include "Orthohedron.h"
#include "InputManager.h"


void Orthohedron::Update(float dt)
{
	// Apply rotation into forward direction
	transform.rotation = transform.rotation + glm::vec3(0.f, 0.f, 1.f) * angularVelocity;

	if (transform.scale.y <= 0.3f)
		scaleVelocity = 0.01f;
	else if (transform.scale.y >= 0.7f)
		scaleVelocity = -0.01f;

	transform.scale.y += scaleVelocity;

	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(ApplyModelMatrix()));
}

void Orthohedron::Draw(GLuint vao)
{
	glUseProgram(SHADERPROGRAM_MANAGER.compiledPrograms[0]);
	glBindVertexArray(vao);

	if (!INPUT_MANAGER.GetPaused()) {
		Update(0.f);
	}
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, NumTotalTriangles());
	glBindVertexArray(0);
}

glm::mat4 Orthohedron::ApplyModelMatrix()
{
	// Create matrix that defines the translation and rotation
	glm::mat4 rotationMatrix = MatrixUtilities::GenerateRotationMatrix(glm::vec3(0.f, 0.f, 1.f), transform.rotation.z);

	glm::mat4 scaleMatrix = MatrixUtilities::GenerateScaleMatrix(transform.scale);

	return rotationMatrix * scaleMatrix * glm::mat4(1.f);
}
