#pragma once
#include "GameObject.h"
#include "ResourceManager.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class Scene {
public:
	glm::vec2 cameraPosition;

	glm::vec2 sceneStartPosition;
	glm::vec2 sceneEndPosition;

	GameObject* player;

	std::vector<GameObject*> backgrounds;
	std::vector<GameObject*> playerBullets;
	std::vector<GameObject*> enemyBullets;
	std::vector<GameObject*> enemies;
	std::vector<GameObject*> obstacles;
	std::vector<GameObject*> items;

	void CreateDefaultScene();

};