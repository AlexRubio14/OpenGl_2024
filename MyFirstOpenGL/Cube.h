#pragma once
#include "GameObject.h"

class Cube : public GameObject
{
private: 

public: 

	Cube()
		: GameObject() {};

	virtual void Update(float dt) override
	{
		// Apply velocity and rotation into forward direction
		transform.position = transform.position + transform.forward * velocity;
		transform.rotation = transform.rotation + transform.rotationDirection * angularVelocity;

		// Invert forward when reached screen limits
		if (transform.position.y >= 0.5f || transform.position.y <= -0.5f) {
			transform.forward = transform.forward * -1.f;
		}
	}

	virtual glm::mat4 ApplyModelMatrix() override
	{
		// Create matrix that defines the translation and rotation 
		glm::mat4 translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);
		glm::mat4 rotationMatrix = MatrixUtilities::GenerateRotationMatrix(transform.rotationDirection, transform.rotation.y);

		return translationMatrix * rotationMatrix * glm::mat4(1.f);
	};


};