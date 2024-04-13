#pragma once
#include <GL/glew.h>
#include <gtc/type_ptr.hpp>
#include <vector>

#include "Transform.h"
#include "MatrixUtilities.h"
#include "ShaderProgramManager.h"

class GameObject
{
protected: 

	Transform transform;

	float velocity; 
	float angularVelocity;
	float scaleVelocity;

	bool isActive;

	std::vector<GLfloat> vertexs;

public:

	GameObject()
		: transform(Transform()), velocity(0.01f), angularVelocity(-1.f), scaleVelocity(1.f), isActive(true) {};

	GameObject(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
		: transform(Transform(_position, _rotation, _scale)), velocity(0.01f), angularVelocity(-1.f), scaleVelocity(1.f), isActive(true) {};

	virtual void Update(float dt) = 0;

	virtual glm::mat4 ApplyModelMatrix() = 0; 

	void Accelerate();

	void Deccelerate();

	inline std::vector<GLfloat> GetVertexs() const { return vertexs; }
	inline int NumTotalTriangles() const { return vertexs.size() / 3; }

	inline Transform GetTransform() const { return transform; }

	inline float GetVelocity() const { return velocity; }
	inline void SetVelocity(const float value) { velocity += value; }

	inline float GetAngularVelocity() const { return angularVelocity; }
	inline void SetAngularVelocity(const float value) { angularVelocity += value; }

	inline float GetScaleVelocity() const { return scaleVelocity; }
	inline void SetScaleVelocity(const float value) { scaleVelocity += value; }

	inline bool GetIsActive() const { return isActive; }
	inline void SetIsActive(const bool value) { isActive = value; }
};