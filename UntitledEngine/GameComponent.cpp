#include "GameComponent.h"

bool GameComponent::IsActive()
{
	return isActive;
}

void GameComponent::SetActive(bool flag)
{
	isActive = flag;
}

void GameComponent::Start()
{
}

void GameComponent::Update(float deltaTime)
{
}
