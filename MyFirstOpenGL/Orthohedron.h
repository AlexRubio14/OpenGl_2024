#pragma once
#include "GameObject.h"

class Orthohedron : public GameObject
{
private:

public:

	Orthohedron()
		: GameObject() {

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
	};

	Orthohedron(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);

	virtual void Update(float _dt) override;

	virtual void Render() override;

	void InitProgramValues() override;
};