#include "Enemy.h"
#include "Scene.h"
#include "Bullet.h"
#include <math.h>

#define M_PI 3.14159265358979323846

void Enemy::Start()
{
	coolDownTimer = 0;
	this->gameObject->AddComponent<Rigidbody>();
	this->gameObject->GetComponent<Rigidbody>()->mass = 1;
	this->gameObject->GetComponent<Rigidbody>()->isLockRotation = true;
	this->gameObject->AddComponent<BoxCollider>();
	this->gameObject->GetComponent<BoxCollider>()->SetSize(16, 32);
	this->gameObject->GetComponent<Enemy>()->moveSpeed = 80;
	this->gameObject->GetComponent<Enemy>()->moveDirection = glm::vec2(0, 0);
	this->gameObject->GetComponent<Enemy>()->facingDirection = glm::vec2(0, 1);
	this->gameObject->GetComponent<Enemy>()->shootVelocity = 160;
	this->gameObject->GetComponent<Enemy>()->isReadyShoot = true;
	this->gameObject->GetComponent<Enemy>()->weaponCoolDownIntervel = 0.4f;
	this->gameObject->GetComponent<Enemy>()->visionRange = 100.0f;
	this->gameObject->GetComponent<Enemy>()->partrolDistance = 10.0f;
	this->gameObject->GetComponent<Enemy>()->isMoveRight = true;
	this->gameObject->GetComponent<Enemy>()->isAttack = true;
	this->gameObject->GetComponent<Enemy>()->initialPos = this->gameObject->position;
}

void Enemy::Update(float deltaTime)
{
	this->gameObject->GetComponent<Rigidbody>()->velocity = moveSpeed * glm::normalize(moveDirection);
	if (moveDirection.x != 0 || moveDirection.y != 0) {
		facingDirection = moveDirection;
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

	Patrol();
}

void Enemy::CalculateRotation()
{
	if (facingDirection.x != facingDirection.x || facingDirection.y != facingDirection.y) {
		facingDirection = glm::vec2(0, 1);
		return;
	}
	float angle;
	float cos = glm::dot(glm::normalize(facingDirection), glm::vec2(1, 0));
	angle = glm::acos(cos) * 180 / M_PI;
	if (angle != angle) {
		return;
	}
	if (facingDirection.y < 0) {
		angle = -angle;
	}
	this->gameObject->rotation = angle;

}

void Enemy::Shoot()
{
	if (!isReadyShoot) {
		return;
	}
	bool isFoundUsedBullet = false;
	for (int i = 0; i < scene->enemyBullets.size(); i++) {
		if (scene->enemyBullets[i]->destroyed) {
			scene->enemyBullets[i]->destroyed = false;
			scene->enemyBullets[i]->position = this->gameObject->position;
			scene->enemyBullets[i]->GetComponent<Rigidbody>()->velocity = glm::normalize(facingDirection) * shootVelocity;
			scene->enemyBullets[i]->GetComponent<Bullet>()->lastPosition = this->gameObject->position;
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
		scene->enemyBullets.push_back(bullet);
	}
	isReadyShoot = false;
}

void Enemy::Patrol()
{
	double d;
	d = sqrt(pow(scene->player->position.x - this->gameObject->position.x, 2)+pow(scene->player->position.y - this->gameObject->position.y,2));
	if (d>visionRange) {
		if (isMoveRight) {
			moveDirection.x = 1;
		}
		else {
			moveDirection.x = -1;
		}

		if (this->gameObject->position.x > initialPos.x + 96) {
			isMoveRight = false;
		}
		else if (this->gameObject->position.x < initialPos.x) {
			isMoveRight = true;
		}
	}
	else {
		moveDirection.x = 0;
		facingDirection.x = scene->player->position.x - this->gameObject->position.x;
		facingDirection.y = scene->player->position.y - this->gameObject->position.y;
		Shoot();

	}
}
