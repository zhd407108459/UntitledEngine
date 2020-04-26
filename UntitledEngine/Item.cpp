#include"Item.h"

void Item :: Start() {
	
	this->gameObject->AddComponent<BoxCollider>();
	this->gameObject->GetComponent<BoxCollider>()->SetSize(16, 32);
}