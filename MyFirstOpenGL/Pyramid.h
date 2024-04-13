#pragma once
#include "GameObject.h"
#include "TimeManager.h"

class Pyramid : public GameObject
{
private:


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

	Pyramid(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
		: GameObject(_position, _rotation, _scale) {

		//Size (0.4 x 0.6 x 0.4)
		vertexs = {
			 +0.0f, +0.5f, +0.0f,
				-0.2f, -0.5f, +0.2f,
				+0.2f, -0.5f, +0.2f,
				+0.2f, -0.5f, -0.2f,
				-0.2f, -0.5f, -0.2f,
				-0.2f, -0.5f, +0.2f,

				// Triangle Strip
				+0.2f, -0.5f, +0.2f,
				-0.2f, -0.5f, +0.2f,
				+0.2f, -0.5f, -0.2f,
				-0.2f, -0.5f, -0.2f,
		};

	};

	virtual void Update(float dt) override;

	virtual void Draw(GLuint vao) override;


	virtual glm::mat4 ApplyModelMatrix() override;
};