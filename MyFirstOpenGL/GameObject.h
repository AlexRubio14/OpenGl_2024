#pragma once
#include <GL/glew.h>
#include <gtc/type_ptr.hpp>
#include <vector>

#include "Transform.h"
#include "MatrixUtilities.h"
#include "TimeManager.h"
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

	virtual void Update(float _dt) = 0;

	virtual void Draw(GLuint _vao) = 0;

	virtual glm::mat4 ApplyModelMatrix() = 0; 

	void Accelerate();

	void Deccelerate();

	inline std::vector<GLfloat> GetVertexs() const { return vertexs; }
	inline int NumTotalTriangles() const { return vertexs.size() / 3; }

	inline Transform GetTransform() const { return transform; }

	inline float GetVelocity() const { return velocity; }
	inline void SetVelocity(const float _value) { velocity += _value; }

	inline float GetAngularVelocity() const { return angularVelocity; }
	inline void SetAngularVelocity(const float _value) { angularVelocity += _value; }

	inline float GetScaleVelocity() const { return scaleVelocity; }
	inline void SetScaleVelocity(const float _value) { scaleVelocity += _value; }

	inline bool GetIsActive() const { return isActive; }
	inline void SetIsActive(const bool _value) { isActive = _value; }
};