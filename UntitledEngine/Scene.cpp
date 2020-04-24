#include "Scene.h"


void Scene::CreateDefaultScene()
{
	sceneStartPosition = glm::vec2(-1280, -720);
	sceneEndPosition = glm::vec2(1280, 720);

	cameraPosition = glm::vec2(-640, -360);

	Texture2D backgroundTexture;
	backgroundTexture = ResourceManager::GetTexture("Background");
	basicBackGround = new GameObject(cameraPosition, glm::vec2(1344, 784), backgroundTexture, glm::vec3(1.0f));

	Texture2D ironTileTexture;
	ironTileTexture = ResourceManager::GetTexture("IronTile"); 
	Texture2D woodTileTexture;
	woodTileTexture = ResourceManager::GetTexture("WoodTile");
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 18; j++) {
			if (i == 0 || i == 31 || j == 0 || j == 17) {
				GameObject* obs = new GameObject(glm::vec2((i - 16) * 32, (j - 9) * 32), glm::vec2(32, 32), ironTileTexture, glm::vec3(1.0f));
				obs->AddComponent<BoxCollider>();
				obs->GetComponent<BoxCollider>()->SetSize(32, 32);
				obs->AddComponent<Rigidbody>();
				obs->GetComponent<Rigidbody>()->mass = 1;
				obs->GetComponent<Rigidbody>()->isStatic = true;
				obstacles.push_back(obs);
			}
			if ((i == 7 || i == 23) && j > 5 && j < 12) {
				GameObject* obs = new GameObject(glm::vec2((i - 16) * 32, (j - 9) * 32), glm::vec2(32, 32), woodTileTexture, glm::vec3(1.0f));
				obs->AddComponent<BoxCollider>();
				obs->GetComponent<BoxCollider>()->SetSize(32, 32);
				obs->AddComponent<Rigidbody>();
				obs->GetComponent<Rigidbody>()->mass = 1;
				obs->GetComponent<Rigidbody>()->isStatic = true;
				obstacles.push_back(obs);
			}
		}
	}


	Texture2D bulletTexture;
	bulletTexture = ResourceManager::GetTexture("Bullet");

	Texture2D enemyTexture;
	enemyTexture = ResourceManager::GetTexture("Enemy");
	GameObject* enemy1 = new GameObject(glm::vec2(0, 160), glm::vec2(32, 32), enemyTexture, glm::vec3(1.0f));
	enemy1->AddComponent<Enemy>();
	enemy1->GetComponent<Enemy>()->scene = this;
	enemy1->GetComponent<Enemy>()->bulletTexture = bulletTexture;
	enemies.push_back(enemy1);

	Texture2D playerTexture;
	playerTexture = ResourceManager::GetTexture("PlayerPistol");
	player = new GameObject(glm::vec2(0, 0), glm::vec2(32, 32), playerTexture, glm::vec3(1.0f));
	player->AddComponent<Player>();
	player->GetComponent<Player>()->scene = this;
	player->GetComponent<Player>()->bulletTexture = bulletTexture;

}
