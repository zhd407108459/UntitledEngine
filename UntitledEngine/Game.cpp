#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "XboxInput.h"
#include <iostream>
#include <math.h>

// Game-related State data
SpriteRenderer* Renderer;
XboxInput* Player1;

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
}

void Game::Init()
{
	// Load shaders
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// Load textures
	ResourceManager::LoadTexture("textures/Soldier1Idle.png", GL_TRUE, "PlayerIdle");
	ResourceManager::LoadTexture("textures/Soldier1AssaultRifle.png", GL_TRUE, "PlayerAssaultRifle");
	ResourceManager::LoadTexture("textures/Soldier1Pistol.png", GL_TRUE, "PlayerPistol");
	ResourceManager::LoadTexture("textures/Soldier4Pistol.png", GL_TRUE, "Enemy");
	ResourceManager::LoadTexture("textures/Background.png", GL_TRUE, "Background");
	ResourceManager::LoadTexture("textures/IronTile.png", GL_TRUE, "IronTile");
	ResourceManager::LoadTexture("textures/WoodTile.png", GL_TRUE, "WoodTile");
	ResourceManager::LoadTexture("textures/Bullet.png", GL_TRUE, "Bullet");
	ResourceManager::LoadTexture("textures/AmmoSupply.png", GL_TRUE, "AmmoSupply");
	ResourceManager::LoadTexture("textures/AssaultRifle.png", GL_TRUE, "AssaultRifle");
	ResourceManager::LoadTexture("textures/Pistol.png", GL_TRUE, "Pistol");
	ResourceManager::LoadTexture("textures/Square.png", GL_TRUE, "Square");
	ResourceManager::LoadTexture("textures/Win.png", GL_TRUE, "Win");
	ResourceManager::LoadTexture("textures/Lose.png", GL_TRUE, "Lose");
	// Set render-specific controls
	Shader myShader;
	myShader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(myShader);

	// Set up the scene
	scene = new Scene();
	scene->LoadSceneFromFile("data/scene.txt");

	for (int i = 0; i < scene->enemies.size(); i++) {
		scene->enemies[i]->Start();
	}

	scene->player->Start();
	
	for (int i = 0; i < scene->items.size(); i++) {
		scene->items[i]->Start();
	}

	Player1 = new XboxInput(1);
}

void Game::Update(GLfloat dt)
{
	//printf("FPS: %f\n", 1.0f / dt);
	//printf("%f\n",scene->enemies[0]->position.x);
	//printf("%f\n", scene->player->GetComponent<Player>()->facingDirection.x);
	//printf("%d\n",scene->enemies.size());
	if (State != GameState::GAME_ACTIVE) {
		return;
	}


	if ((scene->basicBackGround->position - scene->cameraPosition).x + 32 > 32) {
		scene->basicBackGround->position.x -= 32;
	}
	if ((scene->basicBackGround->position - scene->cameraPosition).x + 32 < -32) {
		scene->basicBackGround->position.x += 32;
	}
	if ((scene->basicBackGround->position - scene->cameraPosition).y + 32 > 32) {
		scene->basicBackGround->position.y -= 32;
	}
	if ((scene->basicBackGround->position - scene->cameraPosition).y + 32 < -32) {
		scene->basicBackGround->position.y += 32;
	}

	for (int i = 0; i < scene->playerBullets.size(); i++) {
		if (!scene->playerBullets[i]->destroyed) {
			scene->playerBullets[i]->Update(dt);
		}
	}

	for (int i = 0; i < scene->enemyBullets.size(); i++) {
		if (!scene->enemyBullets[i]->destroyed) {
			scene->enemyBullets[i]->Update(dt);
		}
	}

	for (int i = 0; i < scene->enemies.size(); i++) {
		if (!scene->enemies[i]->destroyed) {
			scene->enemies[i]->Update(dt);
		}
	}

	for (int i = 0; i < scene->items.size(); i++) {
		if (!scene->items[i]->destroyed) {
			scene->items[i]->Update(dt);
		}
	}
	if (!scene->player->destroyed) {
		scene->player->Update(dt);
	}

	scene->cameraPosition = scene->player->position + glm::vec2(-624, -344);

	HandleCollisions();

	bool isWin = true;
	for (int i = 0; i < scene->enemies.size(); i++) {
		if (!scene->enemies[i]->destroyed) {
			isWin = false;
			break;
		}
	}
	if (isWin) {
		//Win
		EndGame(true);
	}

	//Xbox Input
	/*if (Player1->IsConnected())
	{
		if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			Player1->Vibrate(65535, 0);
		}

		if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			Player1->Vibrate(0, 65535);
		}

		if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
		{
			Player1->Vibrate(65535, 65535);
		}

		if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			Player1->Vibrate();
		}



	}
	else
	{
		std::cout << "\n\tERROR! PLAYER 1 - XBOX 360 Controller Not Found!\n";
		std::cout << "Press Any Key To Exit.";
		//std::cin.get();
		
	}*/

	for (int i = 0; i < scene->playerBullets.size(); i++) {
		scene->playerBullets[i]->GetComponent<Bullet>()->lastPosition = scene->playerBullets[i]->position;
	}
	for (int i = 0; i < scene->enemyBullets.size(); i++) {
		scene->enemyBullets[i]->GetComponent<Bullet>()->lastPosition = scene->enemyBullets[i]->position;
	}
}


void Game::ProcessInput(GLfloat dt)
{
	
	if (State != GameState::GAME_ACTIVE) {
		if (Keys[84]) {//T
			Restart();
		}
		return;
	}
	bool isMYZ = false, isMXZ = false, isFYZ = false, isFXZ = false;
	if (Player1->IsConnected()) {
		
		if (Player1->GetState().Gamepad.bRightTrigger)
		{
			scene->player->GetComponent<Player>()->Shoot();
		}
		
		if (Player1->GetState().Gamepad.sThumbLX > 5000) {
			scene->player->GetComponent<Player>()->moveDirection.x = Player1->GetState().Gamepad.sThumbLX;
		}
		else if (Player1->GetState().Gamepad.sThumbLX < -5000) {
			scene->player->GetComponent<Player>()->moveDirection.x = Player1->GetState().Gamepad.sThumbLX;
		}
		else {
			scene->player->GetComponent<Player>()->moveDirection.x = 0;
			isMXZ = true;
		}
		if (Player1->GetState().Gamepad.sThumbLY > 5000) {
			scene->player->GetComponent<Player>()->moveDirection.y = -Player1->GetState().Gamepad.sThumbLY;
		}
		else if (Player1->GetState().Gamepad.sThumbLY < -5000) {
			scene->player->GetComponent<Player>()->moveDirection.y = -Player1->GetState().Gamepad.sThumbLY;
		}
		else {
			scene->player->GetComponent<Player>()->moveDirection.y = 0;
			isMYZ = true;
		}

		if (Player1->GetState().Gamepad.sThumbRX > 3000) {
			scene->player->GetComponent<Player>()->facingDirection.x = Player1->GetState().Gamepad.sThumbRX;
		}
		else if (Player1->GetState().Gamepad.sThumbRX < -3000) {
			scene->player->GetComponent<Player>()->facingDirection.x = Player1->GetState().Gamepad.sThumbRX;
		}
		else {
			isFYZ = true;
			//scene->player->GetComponent<Player>()->facingDirection.y = 0;
		}
		if (Player1->GetState().Gamepad.sThumbRY > 3000) {
			scene->player->GetComponent<Player>()->facingDirection.y = -Player1->GetState().Gamepad.sThumbRY;
		}
		else if (Player1->GetState().Gamepad.sThumbRY < -3000) {
			scene->player->GetComponent<Player>()->facingDirection.y = -Player1->GetState().Gamepad.sThumbRY;
		}
		else {
			isFXZ = true;
			//scene->player->GetComponent<Player>()->facingDirection.y = 0;
		}

		
	}
	else {
		if (scene->player->GetComponent<Player>()->moveDirection.x != 0 || scene->player->GetComponent<Player>()->moveDirection.y != 0) {
			scene->player->GetComponent<Player>()->facingDirection = scene->player->GetComponent<Player>()->moveDirection;
		}
	}
	if (Keys[87]) {//W
		scene->player->GetComponent<Player>()->moveDirection.y = -1;
		isMYZ = false;
	}
	else if (Keys[83]) {//S
		scene->player->GetComponent<Player>()->moveDirection.y = 1;
		isMYZ = false;
	}
	else{
		if (!Player1->IsConnected() || isMYZ) {
			scene->player->GetComponent<Player>()->moveDirection.y = 0;
		}
	}
	if (Keys[65]) {//A
		scene->player->GetComponent<Player>()->moveDirection.x = -1;
		isMXZ = false;
	}
	else if (Keys[68]) {//D
		scene->player->GetComponent<Player>()->moveDirection.x = 1;
		isMXZ = false;
	}
	else {
		if (!Player1->IsConnected() || isMXZ) {
			scene->player->GetComponent<Player>()->moveDirection.x = 0;
		}
	}
	if (isFYZ && isFXZ && (!isMXZ || !isMYZ)) {
		scene->player->GetComponent<Player>()->facingDirection = scene->player->GetComponent<Player>()->moveDirection;
	}
	if (Keys[32]) {//Space
		scene->player->GetComponent<Player>()->Shoot();
	}
}

void Game::Render()
{
	scene->basicBackGround->Draw(*Renderer, scene->cameraPosition);

	for (int i = 0; i < scene->obstacles.size(); i++) {
		if (IsInScreen(scene->obstacles[i]->position)) {
			scene->obstacles[i]->Draw(*Renderer, scene->cameraPosition);
		}
	}

	for (int i = 0; i < scene->playerBullets.size(); i++) {
		if (IsInScreen(scene->playerBullets[i]->position) && !scene->playerBullets[i]->destroyed) {
			scene->playerBullets[i]->Draw(*Renderer, scene->cameraPosition);
		}
	}

	for (int i = 0; i < scene->enemyBullets.size(); i++) {
		if (IsInScreen(scene->enemyBullets[i]->position) && !scene->enemyBullets[i]->destroyed) {
			scene->enemyBullets[i]->Draw(*Renderer, scene->cameraPosition);
		}
	}

	for (int i = 0; i < scene->enemies.size(); i++) {
		if (IsInScreen(scene->enemies[i]->position) && !scene->enemies[i]->destroyed) {
			scene->enemies[i]->Draw(*Renderer, scene->cameraPosition);
		}
	}

	if (!scene->player->destroyed){
		scene->player->Draw(*Renderer, scene->cameraPosition);
		
	}
	for (int i = 0; i < scene->items.size(); i++) {
		if (!scene->items[i]->destroyed) {
			scene->items[i]->Draw(*Renderer, scene->cameraPosition);
		}
			
	}
	
	if (State == GameState::GAME_WIN) {
		Texture2D winTexture;
		winTexture = ResourceManager::GetTexture("Win");
		Renderer->DrawSprite(winTexture, glm::vec2(0, 0), glm::vec2(1280, 720), 0, glm::vec3(1.0f));
	}
	else if (State == GameState::GAME_LOSE) {
		Texture2D loseTexture;
		loseTexture = ResourceManager::GetTexture("Lose");
		Renderer->DrawSprite(loseTexture, glm::vec2(0, 0), glm::vec2(1280, 720), 0, glm::vec3(1.0f));
	}

}

bool Game::IsInScreen(glm::vec2 pos)
{
	if ((pos - scene->cameraPosition).x > -32 && (pos - scene->cameraPosition).x < 1280 && (pos - scene->cameraPosition).y > -32 && (pos - scene->cameraPosition).y < 720) {
		return true;
	}
	else {
		return false;
	}
}

void Game::HandleCollisions()
{
	//Handle collisions between obstacles and player/enemies
	for (int i = 0; i < scene->obstacles.size(); i++) {
		glm::vec2 hitpoint1;
		bool isOverlapping = IsOverlapping(*(scene->obstacles[i]->GetComponent<BoxCollider>()), *(scene->player->GetComponent<BoxCollider>()), hitpoint1);
		if (isOverlapping) {
			HandleCollisionForRigidbody(scene->player->GetComponent<Rigidbody>(), scene->obstacles[i]->GetComponent<Rigidbody>(), scene->player->GetComponent<BoxCollider>(), scene->obstacles[i]->GetComponent<BoxCollider>(), hitpoint1);
		}
		for (int j = 0; j < scene->enemies.size(); j++) {
			if (scene->enemies[j]->destroyed) {
				continue;
			}
			glm::vec2 hitpoint;
			bool isOverlapping = IsOverlapping(*(scene->obstacles[i]->GetComponent<BoxCollider>()), *(scene->enemies[j]->GetComponent<BoxCollider>()), hitpoint);
			if (isOverlapping) {
				HandleCollisionForRigidbody(scene->enemies[j]->GetComponent<Rigidbody>(), scene->obstacles[i]->GetComponent<Rigidbody>(), scene->enemies[j]->GetComponent<BoxCollider>(), scene->obstacles[i]->GetComponent<BoxCollider>(), hitpoint);
			}
		}
	}
	//Handle collisions between player and enemies
	for (int i = 0; i < scene->enemies.size(); i++) {
		if (scene->enemies[i]->destroyed) {
			continue;
		}
		glm::vec2 hitpoint;
		bool isOverlapping = IsOverlapping(*(scene->enemies[i]->GetComponent<BoxCollider>()), *(scene->player->GetComponent<BoxCollider>()), hitpoint);
		if (isOverlapping) {
			HandleCollisionForRigidbody(scene->player->GetComponent<Rigidbody>(), scene->enemies[i]->GetComponent<Rigidbody>(), scene->player->GetComponent<BoxCollider>(), scene->enemies[i]->GetComponent<BoxCollider>(), hitpoint);
		}
	}
	//Handle collisions between player's bullets and enemies/obstacles
	for (int i = 0; i < scene->playerBullets.size(); i++) {
		if (!scene->playerBullets[i]->destroyed) {
			for (int j = 0; j < scene->obstacles.size(); j++) {
				HitInfo hit;
				Line line;
				line.startPoint = scene->playerBullets[i]->GetComponent<Bullet>()->lastPosition;
				line.endPoint = scene->playerBullets[i]->position;
				bool isIntersecting = LinecastCollider(line, *(scene->obstacles[j]->GetComponent<BoxCollider>()), hit);
				if (isIntersecting) {
					//printf("HIT\n");
					scene->playerBullets[i]->destroyed = true;
					break;
				}
			}
		}
		if (!scene->playerBullets[i]->destroyed) {
			for (int j = 0; j < scene->enemies.size(); j++) {
				if (scene->enemies[j]->destroyed) {
					continue;
				}
				HitInfo hit;
				Line line;
				line.startPoint = scene->playerBullets[i]->GetComponent<Bullet>()->lastPosition;
				line.endPoint = scene->playerBullets[i]->position;
				bool isIntersecting = LinecastCollider(line, *(scene->enemies[j]->GetComponent<BoxCollider>()), hit);
				if (isIntersecting) {
					scene->playerBullets[i]->destroyed = true;
					scene->enemies[j]->destroyed = true;
					scene->SoundEngine->play2D("audio/Death.wav", false);
					//scene->enemies.erase(scene->enemies.begin()+j);
					break;
				}
			}
		}
		
	}
	//handle collisions between enemies' bullets and players/obstacles
	for (int i = 0; i < scene->enemyBullets.size(); i++) {
		if (!scene->enemyBullets[i]->destroyed) {
			for (int j = 0; j < scene->obstacles.size(); j++) {
				HitInfo hit;
				Line line;
				line.startPoint = scene->enemyBullets[i]->GetComponent<Bullet>()->lastPosition;
				line.endPoint = scene->enemyBullets[i]->position;
				bool isIntersecting = LinecastCollider(line, *(scene->obstacles[j]->GetComponent<BoxCollider>()), hit);
				if (isIntersecting) {
					scene->enemyBullets[i]->destroyed = true;
					break;
				}
			}
		}
		if (!scene->enemyBullets[i]->destroyed) {
			HitInfo hit;
			Line line;
			line.startPoint = scene->enemyBullets[i]->GetComponent<Bullet>()->lastPosition;
			line.endPoint = scene->enemyBullets[i]->position;
			bool isIntersecting = LinecastCollider(line, *(scene->player->GetComponent<BoxCollider>()), hit);
			if (isIntersecting) {
				//printf("HIT");
				scene->enemyBullets[i]->destroyed = true;
				scene->player->destroyed = true;
				//Lose
				EndGame(false);
				break;
			}
		}

	}
	//handle collisions between items and players
	for (int i = 0; i < scene->items.size(); i++) {
		if (!scene->items[i]->destroyed) {
			glm::vec2 hitpoint;
			bool isOverlapping = IsOverlapping(*(scene->items[i]->GetComponent<BoxCollider>()), *(scene->player->GetComponent<BoxCollider>()), hitpoint);
			if (isOverlapping) {
				scene->items[i]->destroyed = true;
				if (scene->items[i]->GetComponent<Item>()->type == 1) {
					scene->player->GetComponent<Player>()->PickUpPistol();
				}
				if (scene->items[i]->GetComponent<Item>()->type == 2) {
					scene->player->GetComponent<Player>()->PickUpAssaultRifle();
				}
				if (scene->items[i]->GetComponent<Item>()->type == 3) {
					scene->player->GetComponent<Player>()->PickUpAmmoSupply();
				}

			}
		}
	}

}

void Game::Restart()
{
	scene = new Scene();
	scene->LoadSceneFromFile("data/scene.txt");

	for (int i = 0; i < scene->enemies.size(); i++) {
		scene->enemies[i]->Start();
	}

	scene->player->Start();

	for (int i = 0; i < scene->items.size(); i++) {
		scene->items[i]->Start();
	}

	Player1 = new XboxInput(1);
	State = GameState::GAME_ACTIVE;
}

void Game::EndGame(bool isWin)
{
	if (State != GameState::GAME_ACTIVE) {
		return;
	}
	if (isWin) {
		State = GameState::GAME_WIN;
		scene->SoundEngine->play2D("audio/Win.wav", false);
	}
	else {
		State = GameState::GAME_LOSE;
		scene->SoundEngine->play2D("audio/Death.wav", false);
	}
}
