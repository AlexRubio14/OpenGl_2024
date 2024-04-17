#pragma once
#include "GameObject.h"

class Pyramid : public GameObject
{
private:

	glm::mat4 rotationMatrixY;

public:

	Pyramid()
		: GameObject() {

		//Size (0.4 x 0.6 x 0.4)
		vertexs = {
		    0.0f, 0.6f, 0.0f, // Apex
		    -0.2f, 0.0f, -0.2f, // Base front left
		    0.2f, 0.0f, -0.2f, // Base front right
		    0.0f, 0.6f, 0.0f, // Apex
		    0.2f, 0.0f, 0.2f, // Base back right
		    0.0f, 0.6f, 0.0f, // Apex
		    -0.2f, 0.0f, 0.2f, // Base back left
		    0.0f, 0.6f, 0.0f, // Apex
		    -0.2f, 0.0f, -0.2f // Base front left
		}; 
	};

	Pyramid(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);

	virtual void Update(float _dt) override;

	virtual void Render() override;

	void InitProgramValues() override;
};