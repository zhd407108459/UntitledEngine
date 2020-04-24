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

	bool isReadyShoot;

	void Start();

	void Update(float deltaTime);

	void CalculateRotation();

	void Shoot();

private:
	float coolDownTimer;

};

