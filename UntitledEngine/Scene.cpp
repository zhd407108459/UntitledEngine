#include "Scene.h"


void Scene::CreateDefaultScene()
{
	SoundEngine = createIrrKlangDevice();
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

void Scene::LoadSceneFromFile(std::string path)
{
	SoundEngine = createIrrKlangDevice();
	glm::vec2 startPos, currentPos;

	cameraPosition = glm::vec2(-640, -360);




	//Generate obstacles
	Texture2D ironTileTexture;
	ironTileTexture = ResourceManager::GetTexture("IronTile");
	Texture2D woodTileTexture;
	woodTileTexture = ResourceManager::GetTexture("WoodTile");

	//Generate enemies and player, and give the, the texture of bullet
	Texture2D bulletTexture;
	bulletTexture = ResourceManager::GetTexture("Bullet");

	//Generate enemies
	Texture2D enemyTexture;
	enemyTexture = ResourceManager::GetTexture("Enemy");
	

	//Generate player
	Texture2D playerIdleTexture;
	playerIdleTexture = ResourceManager::GetTexture("PlayerIdle");
	Texture2D playerPistolTexture;
	playerPistolTexture = ResourceManager::GetTexture("PlayerPistol");
	Texture2D playerAssaultRifleTexture;
	playerAssaultRifleTexture = ResourceManager::GetTexture("PlayerAssaultRifle");


	Texture2D itemPistolTexture;
	itemPistolTexture = ResourceManager::GetTexture("Pistol");
	Texture2D itemAssaultRifleTexture;
	itemAssaultRifleTexture = ResourceManager::GetTexture("AssaultRifle");
	Texture2D itemAmmoSupplyTexture;
	itemAmmoSupplyTexture = ResourceManager::GetTexture("AmmoSupply");

	


	ifstream file(path);

	string line;

	if (file)
	{
		getline(file, line);
		vector<int> firstLineArray;
		stringstream ss(line);
		int temp;
		while (ss >> temp) {
			firstLineArray.push_back(temp);
		}
		if (firstLineArray.size() < 2) {
			cout << "error file" << endl;
			return;
		}
		startPos.x = firstLineArray[0];
		startPos.y = firstLineArray[1];
		currentPos = startPos;
		while (getline(file, line))
		{
			for (int i = 0; i < line.length(); i++) {
				if (line.at(i) == '0') {//empty
					
				}
				else if (line.at(i) == '1') {//player
					player = new GameObject(currentPos, glm::vec2(32, 32), playerIdleTexture, glm::vec3(1.0f));
					player->AddComponent<Player>();
					player->GetComponent<Player>()->scene = this;
					player->GetComponent<Player>()->playerIdleTexture = playerIdleTexture;
					player->GetComponent<Player>()->playerPistolTexture = playerPistolTexture;
					player->GetComponent<Player>()->playerAssaultRifleTexture = playerAssaultRifleTexture;
					player->GetComponent<Player>()->bulletTexture = bulletTexture;
				}
				else if (line.at(i) == '2') {//enemy
					GameObject* enemy1 = new GameObject(currentPos, glm::vec2(32, 32), enemyTexture, glm::vec3(1.0f));
					enemy1->AddComponent<Enemy>();
					enemy1->GetComponent<Enemy>()->scene = this;
					enemy1->GetComponent<Enemy>()->bulletTexture = bulletTexture;
					enemies.push_back(enemy1);
				}
				else if (line.at(i) == '3') {//wood tile
					GameObject* obs = new GameObject(currentPos, glm::vec2(32, 32), woodTileTexture, glm::vec3(1.0f));
					obs->AddComponent<BoxCollider>();
					obs->GetComponent<BoxCollider>()->SetSize(32, 32);
					obs->AddComponent<Rigidbody>();
					obs->GetComponent<Rigidbody>()->mass = 1;
					obs->GetComponent<Rigidbody>()->isStatic = true;
					obstacles.push_back(obs);
				}
				else if (line.at(i) == '4') {//iron tile
					GameObject* obs = new GameObject(currentPos, glm::vec2(32, 32), ironTileTexture, glm::vec3(1.0f));
					obs->AddComponent<BoxCollider>();
					obs->GetComponent<BoxCollider>()->SetSize(32, 32);
					obs->AddComponent<Rigidbody>();
					obs->GetComponent<Rigidbody>()->mass = 1;
					obs->GetComponent<Rigidbody>()->isStatic = true;
					obstacles.push_back(obs);
				}
				else if (line.at(i) == '5') {//pistol
					GameObject* item = new GameObject(currentPos, glm::vec2(32, 32), itemAssaultRifleTexture, glm::vec3(1.0f));
					item->AddComponent<Item>();
					item->GetComponent<Item>()->scene = this;
					item->GetComponent<Item>()->pistolTexture = itemPistolTexture;
					item->GetComponent<Item>()->assaultRifleTexture = itemAssaultRifleTexture;
					item->GetComponent<Item>()->ammoSupplyTexture = itemAmmoSupplyTexture;
					item->GetComponent<Item>()->SetTypeTexture(1);
					items.push_back(item);
				}
				else if (line.at(i) == '6') {//ar
					GameObject* item = new GameObject(currentPos, glm::vec2(32, 32), itemAssaultRifleTexture, glm::vec3(1.0f));
					item->AddComponent<Item>();
					item->GetComponent<Item>()->scene = this;
					item->GetComponent<Item>()->pistolTexture = itemPistolTexture;
					item->GetComponent<Item>()->assaultRifleTexture = itemAssaultRifleTexture;
					item->GetComponent<Item>()->ammoSupplyTexture = itemAmmoSupplyTexture;
					item->GetComponent<Item>()->SetTypeTexture(2);
					items.push_back(item);
				}
				else if (line.at(i) == '7') {//ammo supply
					GameObject* item = new GameObject(currentPos, glm::vec2(32, 32), itemAssaultRifleTexture, glm::vec3(1.0f));
					item->AddComponent<Item>();
					item->GetComponent<Item>()->scene = this;
					item->GetComponent<Item>()->pistolTexture = itemPistolTexture;
					item->GetComponent<Item>()->assaultRifleTexture = itemAssaultRifleTexture;
					item->GetComponent<Item>()->ammoSupplyTexture = itemAmmoSupplyTexture;
					item->GetComponent<Item>()->SetTypeTexture(3);
					items.push_back(item);
				}
				currentPos.x += 32;
			}
			currentPos.x = startPos.x;
			currentPos.y += 32;
		}

		//Generate basic background
		Texture2D backgroundTexture;
		backgroundTexture = ResourceManager::GetTexture("Background");
		basicBackGround = new GameObject(player->position + cameraPosition, glm::vec2(1344, 784), backgroundTexture, glm::vec3(1.0f));
	}
	else
	{
		cout << "no such file" << endl;
		return;
	}


}
