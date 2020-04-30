#pragma once
#include "GameObject.h"
#include "ResourceManager.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Item.h"



class Scene {
public:
	glm::vec2 cameraPosition;

	GameObject* player;

	GameObject* basicBackGround;

	GameObject* win;
	GameObject* lose;

	std::vector<GameObject*> backgrounds;
	std::vector<GameObject*> playerBullets;
	std::vector<GameObject*> enemyBullets;
	std::vector<GameObject*> enemies;
	std::vector<GameObject*> obstacles;
	std::vector<GameObject*> items;

	void CreateDefaultScene();

};