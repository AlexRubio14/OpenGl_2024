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

	unsigned int numVertexs;

	std::vector<GLfloat> vertexs;

	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;

	GLuint VAO;
	GLuint VBO;

public:

	GameObject()
		: transform(Transform()), velocity(0.01f), angularVelocity(1.f), scaleVelocity(1.f), isActive(true) {};

	GameObject(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
		: transform(Transform(_position, _rotation, _scale)), velocity(1.f), angularVelocity(100.f), scaleVelocity(100.f), isActive(true) {};

	~GameObject();

	virtual void Update(float _dt) = 0;

	virtual void Render() = 0;

	inline std::vector<GLfloat> GetVertexs() const { return vertexs; }

	inline Transform GetTransform() const { return transform; }

	inline float GetVelocity() const { return velocity; }
	inline void AddVelocity(const float _value) { velocity += _value; }

	inline float GetAngularVelocity() const { return angularVelocity; }
	inline void SetAngularVelocity(const float _value) { angularVelocity += _value; }

	inline float GetScaleVelocity() const { return scaleVelocity; }
	inline void SetScaleVelocity(const float _value) { scaleVelocity += _value; }

	inline bool GetIsActive() const { return isActive; }
	inline void SetIsActive(const bool _value) { isActive = _value; }

	virtual void InitProgramValues() = 0; 
};