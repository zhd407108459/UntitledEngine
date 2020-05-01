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
	
	int type;

	Texture2D pistolTexture;
	Texture2D assaultRifleTexture;
	Texture2D ammoSupplyTexture;

	void SetTypeTexture(int i);

	void Start();
};

