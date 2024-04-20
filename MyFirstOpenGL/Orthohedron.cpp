#include "Orthohedron.h"
#include "GLManager.h"

Orthohedron::Orthohedron(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	: GameObject(_position, _rotation, _scale) {

	//Size (0.4 x 0.6 x 0.4)
	vertexs = {
		-0.2f, +0.6f, -0.2f, // 3
		+0.2f, +0.6f, -0.2f, // 2
		-0.2f, -0.6f, -0.2f, // 6
		+0.2f, -0.6f, -0.2f, // 7
		+0.2f, -0.6f, +0.2f, // 4
		+0.2f, +0.6f, -0.2f, // 2
		+0.2f, +0.6f, +0.2f, // 0
		-0.2f, +0.6f, -0.2f, // 3
		-0.2f, +0.6f, +0.2f, // 1
		-0.2f, -0.6f, -0.2f, // 6
		-0.2f, -0.6f, +0.2f, // 5
		+0.2f, -0.6f, +0.2f, // 4
		-0.2f, +0.6f, +0.2f, // 1
		+0.2f, +0.6f, +0.2f  // 0
	};
	
	// Assing num of vertex
	numVertexs = (unsigned int)vertexs.size() / 3;

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

void Orthohedron::Update(float _dt)
{
	// Apply rotation into forward direction
	transform.rotation = transform.rotation + (glm::vec3(0.f, 0.f, 1.f) * angularVelocity) * _dt;

	if (transform.scale.y <= 0.3f)
		scaleVelocity = 1.f;
	else if (transform.scale.y >= 1.f)
		scaleVelocity = -1.f;

	transform.scale.y += scaleVelocity * _dt;

	translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);
	rotationMatrix = MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.z);
	scaleMatrix = MatrixUtilities::GenerateScaleMatrix(transform.scale);

	glUseProgram(SHADERPROGRAM_MANAGER.compiledPrograms[1]);

	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[1], "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[1], "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[1], "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));
}
 
void Orthohedron::Render()
{
	glUseProgram(SHADERPROGRAM_MANAGER.compiledPrograms[1]);
	glBindVertexArray(VAO);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, numVertexs);
	glGetError();

	glBindVertexArray(0);
}

void Orthohedron::InitProgramValues()
{
	glUseProgram(SHADERPROGRAM_MANAGER.compiledPrograms[1]);
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[1], "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[1], "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[1], "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));

	glUniform2f(glGetUniformLocation(SHADERPROGRAM_MANAGER.compiledPrograms[1], "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);
}
