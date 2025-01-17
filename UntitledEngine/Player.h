#pragma once
#include "GameComponent.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "Collider.h"

class Scene;

class Player : public GameComponent
{
public:
	Scene* scene;

	Texture2D bulletTexture;

	Texture2D playerIdleTexture;

	Texture2D playerPistolTexture;

	Texture2D playerAssaultRifleTexture;

	int currentWeapon;//0 empty 1 pistol 2 rifle

	float moveSpeed;

	glm::vec2 moveDirection;

	glm::vec2 facingDirection;

	float shootVelocity;

	int remainAmmo;

	float weaponCoolDownIntervel;

	bool isReadyShoot;

	void Start();

	void Update(float deltaTime);

	void CalculateRotation();

	void Shoot();

	void ClearWeapon();

	void PickUpPistol();

	void PickUpAssaultRifle();

	void PickUpAmmoSupply();

private:

	float coolDownTimer;

};

