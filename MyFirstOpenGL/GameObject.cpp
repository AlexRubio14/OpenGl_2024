#include "GameObject.h"

void GameObject::Accelerate()
{
	velocity += velocity * 0.1f;
	angularVelocity += angularVelocity * 0.1f;
	scaleVelocity += scaleVelocity * 0.1f;
}

void GameObject::Deccelerate()
{
	velocity += (velocity * 0.1f) * -1;
	angularVelocity += (angularVelocity * 0.1f) * -1;
	scaleVelocity += (scaleVelocity * 0.1f) * -1;
}