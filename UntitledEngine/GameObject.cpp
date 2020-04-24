#include "GameObject.h"


GameObject::GameObject()
	: position(0, 0), size(1, 1), color(1.0f), rotation(0.0f), sprite(), destroyed(false) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color)
	: position(pos), size(size), color(color), rotation(0.0f), sprite(sprite), destroyed(false) { }

void GameObject::Draw(SpriteRenderer& renderer, glm::vec2 cameraPos)
{
	renderer.DrawSprite(this->sprite, this->position - cameraPos, this->size, this->rotation, this->color);
}

void GameObject::Start()
{
	for (std::unordered_map<std::type_index, GameComponent*>::iterator iter = components.begin(); iter != components.end(); iter++)
	{
		if (iter->second->IsActive()) {
			iter->second->Start();
		}
	}
}

void GameObject::Update(float deltaTime)
{
	for (std::unordered_map<std::type_index, GameComponent*>::iterator iter = components.begin(); iter != components.end(); iter++)
	{
		if (iter->second->IsActive()) {
			iter->second->Update(deltaTime);
		}
	}
}
