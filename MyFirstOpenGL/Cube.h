#pragma once
#include "GameObject.h"

class Cube : public GameObject
{
private: 

public: 

	Cube()
		: GameObject() {
		
		//Size (0.4 x 0.4 x 0.4)
		vertexs = {
			-0.2f, +0.2f, -0.2f, // 3
			+0.2f, +0.2f, -0.2f, // 2
			-0.2f, -0.2f, -0.2f, // 6
			+0.2f, -0.2f, -0.2f, // 7
			+0.2f, -0.2f, +0.2f, // 4
			+0.2f, +0.2f, -0.2f, // 2
			+0.2f, +0.2f, +0.2f, // 0
			-0.2f, +0.2f, -0.2f, // 3
			-0.2f, +0.2f, +0.2f, // 1
			-0.2f, -0.2f, -0.2f, // 6
			-0.2f, -0.2f, +0.2f, // 5
			+0.2f, -0.2f, +0.2f, // 4
			-0.2f, +0.2f, +0.2f, // 1
			+0.2f, +0.2f, +0.2f  // 0
		};
	};

	Cube(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
		: GameObject(_position, _rotation, _scale) {

		//Size (0.4 x 0.4 x 0.4)
		vertexs = {
			-0.2f, +0.2f, -0.2f, // 3
			+0.2f, +0.2f, -0.2f, // 2
			-0.2f, -0.2f, -0.2f, // 6
			+0.2f, -0.2f, -0.2f, // 7
			+0.2f, -0.2f, +0.2f, // 4
			+0.2f, +0.2f, -0.2f, // 2
			+0.2f, +0.2f, +0.2f, // 0
			-0.2f, +0.2f, -0.2f, // 3
			-0.2f, +0.2f, +0.2f, // 1
			-0.2f, -0.2f, -0.2f, // 6
			-0.2f, -0.2f, +0.2f, // 5
			+0.2f, -0.2f, +0.2f, // 4
			-0.2f, +0.2f, +0.2f, // 1
			+0.2f, +0.2f, +0.2f  // 0
		};
	};

	virtual void Update(float dt) override;

	virtual glm::mat4 ApplyModelMatrix() override;
};