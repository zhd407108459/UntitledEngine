#include "Player.h"
#include "Scene.h"
#include "Bullet.h"
#include "XboxInput.h"

#define M_PI 3.14159265358979323846


void Player::Start()
{
	coolDownTimer = 0;
	this->gameObject->AddComponent<Rigidbody>();
	this->gameObject->GetComponent<Rigidbody>()->mass = 1;
	this->gameObject->GetComponent<Rigidbody>()->isLockRotation = true;
	this->gameObject->AddComponent<BoxCollider>();
	this->gameObject->GetComponent<BoxCollider>()->SetSize(16, 32);
	this->gameObject->GetComponent<Player>()->moveSpeed = 80;
	this->gameObject->GetComponent<Player>()->moveDirection = glm::vec2(0, 0);
	this->gameObject->GetComponent<Player>()->facingDirection = glm::vec2(0, 1);
	this->gameObject->GetComponent<Player>()->shootVelocity = 160;
	this->gameObject->GetComponent<Player>()->isReadyShoot = true;
	this->gameObject->GetComponent<Player>()->weaponCoolDownIntervel = 0.4f;
	this->gameObject->GetComponent<Player>()->remainAmmo = 0; 
	this->gameObject->GetComponent<Player>()->ClearWeapon();
}

void Player::Update(float deltaTime)
{
	this->gameObject->GetComponent<Rigidbody>()->velocity = moveSpeed * glm::normalize(moveDirection);
	if ((moveDirection.x != 0 || moveDirection.y != 0)) {
		//facingDirection = moveDirection;
	}
	CalculateRotation();
	//Cooldown Timer
	if (!isReadyShoot) {
		coolDownTimer += deltaTime;
		if (coolDownTimer >= weaponCoolDownIntervel) {
			coolDownTimer = 0;
			isReadyShoot = true;
		}
	}
}

void Player::CalculateRotation()
{
	if (facingDirection.x != facingDirection.x || facingDirection.y != facingDirection.y) {
		facingDirection = glm::vec2(0, 1);
		return;
	}
	float angle;
	float cos = glm::dot(glm::normalize(facingDirection), glm::vec2(1, 0));
	angle = glm::acos(cos) * 180/ M_PI;
	if (angle != angle) {
		return;
	}
	if (facingDirection.y < 0) {
		angle = -angle;
	}
	this->gameObject->rotation = angle;

}

void Player::Shoot()
{
	if (!isReadyShoot || remainAmmo == 0 || currentWeapon == 0) {
		return;
	}
	bool isFoundUsedBullet = false;
	for (int i = 0; i < scene->playerBullets.size(); i++) {
		if (scene->playerBullets[i]->destroyed) {
			scene->playerBullets[i]->destroyed = false;
			scene->playerBullets[i]->position = this->gameObject->position;
			scene->playerBullets[i]->GetComponent<Rigidbody>()->velocity = glm::normalize(facingDirection) * shootVelocity;
			scene->playerBullets[i]->GetComponent<Bullet>()->lastPosition = this->gameObject->position;
			isFoundUsedBullet = true;
			break;
		}
	}
	if (!isFoundUsedBullet) {
		GameObject* bullet = new GameObject(this->gameObject->position, glm::vec2(32, 32), bulletTexture, glm::vec3(1.0f));
		bullet->AddComponent<Rigidbody>();
		bullet->GetComponent<Rigidbody>()->mass = 1;
		bullet->GetComponent<Rigidbody>()->velocity = glm::normalize(facingDirection) * shootVelocity;
		bullet->AddComponent<Bullet>();
		bullet->GetComponent<Bullet>()->lastPosition = this->gameObject->position;
		scene->playerBullets.push_back(bullet);
	}
	remainAmmo--;
	scene->SoundEngine->play2D("audio/ShootBullet.wav", false);
	isReadyShoot = false;
}

void Player::ClearWeapon()
{
	this->currentWeapon = 0;
	this->gameObject->sprite = this->playerIdleTexture;
}

void Player::PickUpPistol()
{
	scene->SoundEngine->play2D("audio/PickUp.wav", false);
	this->currentWeapon = 1;
	this->gameObject->sprite = this->playerPistolTexture;
	this->weaponCoolDownIntervel = 0.4f;
	this->remainAmmo = 7;
}

void Player::PickUpAssaultRifle()
{
	scene->SoundEngine->play2D("audio/PickUp.wav", false);
	this->currentWeapon = 2;
	this->gameObject->sprite = this->playerAssaultRifleTexture; 
	this->weaponCoolDownIntervel = 0.2f;
	this->remainAmmo = 20;
}

void Player::PickUpAmmoSupply()
{
	scene->SoundEngine->play2D("audio/PickUp.wav", false);
	if (this->currentWeapon == 1) {
		this->remainAmmo = 7;
	}
	if (this->currentWeapon == 2) {
		this->remainAmmo = 20;
	}
}
