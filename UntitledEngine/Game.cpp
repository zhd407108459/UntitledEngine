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
	ResourceManager::LoadTexture("textures/awesomeface.png", GL_TRUE, "face");
	// Set render-specific controls
	Shader myShader;
	myShader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(myShader);
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(GLfloat dt)
{

}

void Game::Render()
{
	Texture2D myTexture;
	myTexture = ResourceManager::GetTexture("face");
	Renderer->DrawSprite(myTexture, glm::vec2(640, 360), glm::vec2(50, 50), 90.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	Renderer->DrawSprite(myTexture, glm::vec2(340, 360), glm::vec2(50, 50), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}