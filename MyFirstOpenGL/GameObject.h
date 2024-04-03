#pragma once
#include "Transform.h"
#include "MatrixUtilities.h"

class GameObject
{
protected: 

	Transform transform;

	float velocity; 
	float angularVelocity; 

public:

	GameObject()
		: transform(Transform()), velocity(0.01f), angularVelocity(-1.f) {};

	virtual void Update(float dt) = 0;

	virtual glm::mat4 ApplyModelMatrix() = 0; 

};