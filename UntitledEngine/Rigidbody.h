#pragma once


#include "GameComponent.h"
#include "Collider.h"
#include "GameObject.h"


class Rigidbody : public GameComponent {
public:
	glm::vec2 velocity;
	float angularVelocity;
	float mass;

	bool isStatic;
	bool isLockPosition;
	bool isLockRotation;

	void AddForce(glm::vec2 force);
	void AddAngularForce(float force);
	void AddForceAtPoint(glm::vec2 force, glm::vec2 point);

	void Update(float deltaTime);


};