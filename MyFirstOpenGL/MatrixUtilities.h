#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


static class MatrixUtilities
{
public:

	static glm::mat4 GenerateTranslationMatrix(glm::vec3 translation) {

		return glm::translate(glm::mat4(1.f), translation);
	}

	static glm::mat4 GenerateRotationMatrix(glm::vec3 axis, float fDegrees) {

		return glm::rotate(glm::mat4(1.f), glm::radians(fDegrees), glm::normalize(axis));
	}
};