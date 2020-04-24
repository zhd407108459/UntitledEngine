#pragma once
#include "GameComponent.h"
#include "GameObject.h"

class Bullet : public GameComponent
{
public:
	glm::vec2 lastPosition;
};

