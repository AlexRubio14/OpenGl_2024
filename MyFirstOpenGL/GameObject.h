#pragma once
#include <GL/glew.h>
#include <vector>

#include "Transform.h"
#include "MatrixUtilities.h"


class GameObject
{
protected: 

	Transform transform;

	float velocity; 
	float angularVelocity; 

	std::vector<GLfloat> vertexs;

public:

	GameObject()
		: transform(Transform()), velocity(0.01f), angularVelocity(-1.f) {};

	GameObject(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
		: transform(Transform(_position, _rotation, _scale)), velocity(0.01f), angularVelocity(-1.f) {};

	virtual void Update(float dt) = 0;

	virtual glm::mat4 ApplyModelMatrix() = 0; 

	inline std::vector<GLfloat> GetVertexs() const { return vertexs; }
	inline int NumTotalTriangles() const { return vertexs.size() / 3; }
};