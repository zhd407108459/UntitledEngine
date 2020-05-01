#include "Scene.h"


void Scene::CreateDefaultScene()
{
	cameraPosition = glm::vec2(-640, -360);

	//Generate basic background
	Texture2D backgroundTexture;
	backgroundTexture = ResourceManager::GetTexture("Background");
	basicBackGround = new GameObject(cameraPosition, glm::vec2(1344, 784), backgroundTexture, glm::vec3(1.0f));



	//Generate obstacles
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

	//Generate enemies and player, and give the, the texture of bullet
	Texture2D bulletTexture;
	bulletTexture = ResourceManager::GetTexture("Bullet");

	//Generate enemies
	Texture2D enemyTexture;
	enemyTexture = ResourceManager::GetTexture("Enemy");
	GameObject* enemy1 = new GameObject(glm::vec2(0, 160), glm::vec2(32, 32), enemyTexture, glm::vec3(1.0f));
	enemy1->AddComponent<Enemy>();
	enemy1->GetComponent<Enemy>()->scene = this;
	enemy1->GetComponent<Enemy>()->bulletTexture = bulletTexture;
	enemies.push_back(enemy1);

	//Generate player
	Texture2D playerIdleTexture;
	playerIdleTexture = ResourceManager::GetTexture("PlayerIdle");
	Texture2D playerPistolTexture;
	playerPistolTexture = ResourceManager::GetTexture("PlayerPistol");
	Texture2D playerAssaultRifleTexture;
	playerAssaultRifleTexture = ResourceManager::GetTexture("PlayerAssaultRifle");

	player = new GameObject(glm::vec2(0, 0), glm::vec2(32, 32), playerIdleTexture, glm::vec3(1.0f));
	player->AddComponent<Player>();
	player->GetComponent<Player>()->scene = this;
	player->GetComponent<Player>()->playerIdleTexture = playerIdleTexture;
	player->GetComponent<Player>()->playerPistolTexture = playerPistolTexture;
	player->GetComponent<Player>()->playerAssaultRifleTexture = playerAssaultRifleTexture;
	player->GetComponent<Player>()->bulletTexture = bulletTexture;

	Texture2D itemPistolTexture;
	itemPistolTexture = ResourceManager::GetTexture("Pistol");
	Texture2D itemAssaultRifleTexture;
	itemAssaultRifleTexture = ResourceManager::GetTexture("AssaultRifle");
	Texture2D itemAmmoSupplyTexture;
	itemAmmoSupplyTexture = ResourceManager::GetTexture("AmmoSupply");

	GameObject* item1 = new GameObject(glm::vec2(-100, 0), glm::vec2(32, 32), itemAssaultRifleTexture, glm::vec3(1.0f));
	item1->AddComponent<Item>();
	item1->GetComponent<Item>()->scene = this;
	item1->GetComponent<Item>()->pistolTexture = itemPistolTexture;
	item1->GetComponent<Item>()->assaultRifleTexture = itemAssaultRifleTexture;
	item1->GetComponent<Item>()->ammoSupplyTexture = itemAmmoSupplyTexture;
	item1->GetComponent<Item>()->SetTypeTexture(1);
	items.push_back(item1);

	GameObject* item2 = new GameObject(glm::vec2(100, 0), glm::vec2(32, 32), itemAssaultRifleTexture, glm::vec3(1.0f));
	item2->AddComponent<Item>();
	item2->GetComponent<Item>()->scene = this;
	item2->GetComponent<Item>()->pistolTexture = itemPistolTexture;
	item2->GetComponent<Item>()->assaultRifleTexture = itemAssaultRifleTexture;
	item2->GetComponent<Item>()->ammoSupplyTexture = itemAmmoSupplyTexture;
	item2->GetComponent<Item>()->SetTypeTexture(2);
	items.push_back(item2);

	GameObject* item3 = new GameObject(glm::vec2(100, 100), glm::vec2(32, 32), itemAssaultRifleTexture, glm::vec3(1.0f));
	item3->AddComponent<Item>();
	item3->GetComponent<Item>()->scene = this;
	item3->GetComponent<Item>()->pistolTexture = itemPistolTexture;
	item3->GetComponent<Item>()->assaultRifleTexture = itemAssaultRifleTexture;
	item3->GetComponent<Item>()->ammoSupplyTexture = itemAmmoSupplyTexture;
	item3->GetComponent<Item>()->SetTypeTexture(3);
	items.push_back(item3);


}
