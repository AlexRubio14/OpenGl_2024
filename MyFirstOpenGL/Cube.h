#pragma once
#include "GameObject.h"

class Cube : public GameObject
{
private: 

public: 

	Cube()
		: GameObject() {};

	virtual void Update(float dt) override;

	virtual glm::mat4 ApplyModelMatrix() override;
};