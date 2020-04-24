#pragma once
#include "GameComponent.h"
#include "GameObject.h"

class Collider : public GameComponent
{

public:
	glm::mat3 GetRotateMatrix() const;
};

class BoxCollider : public Collider {
private:
	glm::vec2 size;
	glm::vec2 offset;

public:
	BoxCollider();
	BoxCollider(float x, float y);
	BoxCollider(glm::vec2 size, glm::vec2 offset);
	~BoxCollider();

	glm::vec2 GetSize() const;
	glm::vec2 GetOffset() const;

	void SetSize(float x, float y);
	void SetSize(glm::vec2 xy);
	void SetOffset(float x, float y);
	void SetOffset(glm::vec2 xy);
};

class CircleCollider : public Collider {
private:
	float radius;
	glm::vec2 offset;

public:
	CircleCollider();
	CircleCollider(float radius);
	CircleCollider(float radius, glm::vec2 offset);
	~CircleCollider();

	float GetRadius() const;
	glm::vec2 GetOffset() const;

	void SetRadius(float radius);
	void SetOffset(float x, float y);
	void SetOffset(glm::vec2 xy);
};

