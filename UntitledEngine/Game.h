#pragma once
#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "PhysicsGeneralMethods.h"

using namespace Physics;

// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_WIN,
	GAME_LOSE
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
	// Game state
	GameState              State;
	GLboolean              Keys[1024];
	GLuint                 Width, Height;

	Scene* scene;

	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();
	// Initialize game state (load all shaders/textures/levels)
	void Init();
	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();

private:
	bool IsInScreen(glm::vec2 pos);
	void HandleCollisions();
	void Restart();
	void EndGame(bool isWin);
};

#endif