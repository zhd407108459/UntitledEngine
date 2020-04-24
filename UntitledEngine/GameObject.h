#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include "Texture.h"
#include "SpriteRenderer.h"
#include "GameComponent.h"

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
	// Object state
	glm::vec2   position, size;
	glm::vec3   color;
	GLfloat     rotation;
	GLboolean   destroyed;
	// Render state
	Texture2D   sprite;

	std::string tag;

	std::unordered_map<std::type_index, GameComponent*> components;

	// Constructor(s)
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));
	// Draw sprite
	virtual void Draw(SpriteRenderer& renderer, glm::vec2 cameraPos);

	template<class T> T* GetComponent();
	template<class T, class... argTs> T* AddComponent(argTs... args);
	template<class T> void RemoveComponent();


	void Start();

	void Update(float deltaTime);
};


template<class T>
inline T* GameObject::GetComponent()
{
	std::type_index id = typeid(T);

	return static_cast<T*>(components.find(id) == components.end() ? nullptr : components[id]);
}

template<class T, class ...argTs>
inline T* GameObject::AddComponent(argTs ...args)
{
	std::type_index id = typeid(T);

	if (components.find(id) != components.end())
		throw "Cannot add duplicated components!";

	T* component = new T(args...);
	static_cast<GameComponent*>(component)->SetActive(true);
	static_cast<GameComponent*>(component)->gameObject = this;

	components[id] = component;

	return component;
}

template<class T>
inline void GameObject::RemoveComponent()
{
	std::type_index id = typeid(T);

	auto it = components.find(id);

	delete it->second;

	if (it != components.end())
		components.erase(it);
}

#endif