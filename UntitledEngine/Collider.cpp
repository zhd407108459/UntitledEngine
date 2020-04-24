#include "Collider.h"
#include <stdio.h>
#define M_PI 3.14159265358979323846

glm::mat3 Collider::GetRotateMatrix() const
{
	glm::mat3 m (1.0f);
	float cos = cosf((gameObject->rotation) * M_PI / 180);
	float sin = sinf((gameObject->rotation) * M_PI / 180);
	m[0][0] = cos;
	m[0][1] = sin;
	m[1][0] = -sin;
	m[1][1] = cos;
	m[2][2] = 1;
	return m;
}

BoxCollider::BoxCollider()
{
	this->size = glm::vec2(1, 1);
	this->offset = glm::vec2(0, 0);
}

BoxCollider::BoxCollider(float x, float y)
{
	this->size = glm::vec2(x, y);
	this->offset = glm::vec2(0, 0);
}

BoxCollider::BoxCollider(glm::vec2 size, glm::vec2 offset)
{
	this->size = size;
	this->offset = offset;
}

BoxCollider::~BoxCollider()
{
}

glm::vec2 BoxCollider::GetSize() const
{
	return this->size;
}

glm::vec2 BoxCollider::GetOffset() const
{
	return this->offset;
}

void BoxCollider::SetSize(float x, float y)
{
	this->size = glm::vec2(x, y);
}

void BoxCollider::SetSize(glm::vec2 xy)
{
	this->size = xy;
}

void BoxCollider::SetOffset(float x, float y)
{
	this->offset = glm::vec2(x, y);
}

void BoxCollider::SetOffset(glm::vec2 xy)
{
	this->offset = xy;
}

CircleCollider::CircleCollider()
{
	this->radius = 1.0f;
	this->offset = glm::vec2(0, 0);
}

CircleCollider::CircleCollider(float radius)
{
	this->radius = radius;
	this->offset = glm::vec2(0,0 );
}

CircleCollider::CircleCollider(float radius, glm::vec2 offset)
{
	this->radius = radius;
	this->offset = offset;
}

CircleCollider::~CircleCollider()
{
}

float CircleCollider::GetRadius() const
{
	return radius;
}

glm::vec2 CircleCollider::GetOffset() const
{
	return offset;
}

void CircleCollider::SetRadius(float radius)
{
	this->radius = radius;
}

void CircleCollider::SetOffset(float x, float y)
{
	this->offset = glm::vec2(x, y);
}

void CircleCollider::SetOffset(glm::vec2 xy)
{
	this->offset = xy;
}


