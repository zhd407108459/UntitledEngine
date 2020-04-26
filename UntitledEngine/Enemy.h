#pragma once
#include "GameComponent.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "Collider.h"

class Scene;

class Enemy : public GameComponent
{
public:
	Scene* scene;

	Texture2D bulletTexture;

	float moveSpeed;

	glm::vec2 moveDirection;

	glm::vec2 facingDirection;

	float shootVelocity;

	float weaponCoolDownIntervel;

	float visionRange;

	float partrolDistance;

	bool isReadyShoot;

	bool isMoveRight;

	bool isAttack;

	void Start();

	void Update(float deltaTime);

	void CalculateRotation();

	void Shoot();

	void Patrol();

private:
	float coolDownTimer;

};

