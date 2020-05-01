#include"Item.h"

void Item::SetTypeTexture(int i)
{
	type = i;
	if (i == 1) {
		this->gameObject->sprite = pistolTexture;
	}
	else if (i == 2) {
		this->gameObject->sprite = assaultRifleTexture;
	}
	else if (i == 3) {
		this->gameObject->sprite = ammoSupplyTexture;
	}
}

void Item :: Start() {
	
	this->gameObject->AddComponent<BoxCollider>();
	this->gameObject->GetComponent<BoxCollider>()->SetSize(16, 32);
}