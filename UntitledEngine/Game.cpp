#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"


// Game-related State data
SpriteRenderer* Renderer;


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
	// Set render-specific controls
	Shader myShader;
	myShader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(myShader);

	// Set up the scene
	scene = new Scene();
	scene->CreateDefaultScene();

	for (int i = 0; i < scene->enemies.size(); i++) {
		scene->enemies[i]->Start();
	}

	scene->player->Start();
}

void Game::Update(GLfloat dt)
{
	printf("FPS: %f\n", 1.0f / dt);
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

	scene->player->Update(dt);
	scene->cameraPosition = scene->player->position + glm::vec2(-624, -344);

	HandleCollisions();

	for (int i = 0; i < scene->playerBullets.size(); i++) {
		scene->playerBullets[i]->GetComponent<Bullet>()->lastPosition = scene->playerBullets[i]->position;
	}
}


void Game::ProcessInput(GLfloat dt)
{
	if (Keys[87]) {//W
		scene->player->GetComponent<Player>()->moveDirection.y = -1;
	}
	else if (Keys[83]) {//S
		scene->player->GetComponent<Player>()->moveDirection.y = 1;
	}
	else {
		scene->player->GetComponent<Player>()->moveDirection.y = 0;
	}
	if (Keys[65]) {//A
		scene->player->GetComponent<Player>()->moveDirection.x = -1;
	}
	else if (Keys[68]) {//D
		scene->player->GetComponent<Player>()->moveDirection.x = 1;
	}
	else {
		scene->player->GetComponent<Player>()->moveDirection.x = 0;
	}

	if (Keys[32]) {//Space
		scene->player->GetComponent<Player>()->Shoot();
	}

	if (Keys[84]) {//T
		Restart();
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

	scene->player->Draw(*Renderer, scene->cameraPosition);
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
					break;
				}
			}
		}
		
	}
}

void Game::Restart()
{
	scene = new Scene();
	scene->CreateDefaultScene();

	for (int i = 0; i < scene->enemies.size(); i++) {
		scene->enemies[i]->Start();
	}

	scene->player->Start();
}
