#include "Rigidbody.h"
#include "PhysicsGeneralMethods.h"
#include <stdio.h>

using namespace Physics;

void Rigidbody::AddForce(glm::vec2 force)
{
	velocity += force / mass;
}

void Rigidbody::AddAngularForce(float force)
{
	angularVelocity += force / mass;
}

void Rigidbody::AddForceAtPoint(glm::vec2 force, glm::vec2 point)
{
	glm::vec2 n = gameObject->position - point;
	float powl = n.x * n.x + n.y * n.y;
	glm::vec2 vforce = force * n * n / powl;
	glm::vec2 aforce = force - vforce;
	float afl = sqrtf(aforce.x * aforce.x + aforce.y * aforce.y)/5;
	if (IsThreePointUnclockwise(gameObject->position.x, gameObject->position.y, point.x, point.y, point.x + aforce.x, point.y + aforce.y)) {
		AddAngularForce(-afl);
	}
	else {
		AddAngularForce(+afl);
	}
	AddForce(vforce);
}

void Rigidbody::Update(float deltaTime)
{
	if (isStatic) {
		return;
	}
	if (!isLockPosition) {
		if ((velocity.x != 0 || velocity.y != 0) && velocity.x == velocity.x && velocity.y == velocity.y) {
			gameObject->position += velocity * deltaTime;
		}
	}
	if (!isLockRotation) {
		if (angularVelocity != 0 && angularVelocity == angularVelocity) {
			gameObject->rotation += angularVelocity * deltaTime;
			if (gameObject->rotation > 360) {
				gameObject->rotation = gameObject->rotation - 360;
			}
		}
	}
}

