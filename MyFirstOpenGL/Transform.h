#pragma once
#include <glm.hpp>

class Transform
{
public: 
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::vec3 forward;

	Transform()
		: position(glm::vec3(0.f)), rotation(glm::vec3(0.f)), scale(glm::vec3(0.f)), forward((glm::vec3(0.f, 1.f, 0.f))) {};

	Transform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
		: position(_position), rotation(_rotation), scale(_scale), forward((glm::vec3(0.f, 1.f, 0.f))) {};
};