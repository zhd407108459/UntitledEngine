#pragma once
#include "GameComponent.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "Collider.h"



class Scene;

class Item : public GameComponent
{
public:
	Scene* scene;
	void Start();
};

