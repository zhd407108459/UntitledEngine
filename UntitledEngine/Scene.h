#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Item.h"
#include <irrklang/irrKlang.h>

using namespace irrklang;

using namespace std;

class Scene {
public:
	glm::vec2 cameraPosition;

	ISoundEngine* SoundEngine;

	GameObject* player;

	GameObject* basicBackGround;


	std::vector<GameObject*> backgrounds;
	std::vector<GameObject*> playerBullets;
	std::vector<GameObject*> enemyBullets;
	std::vector<GameObject*> enemies;
	std::vector<GameObject*> obstacles;
	std::vector<GameObject*> items;

	void CreateDefaultScene();

	void LoadSceneFromFile(std::string path);
};