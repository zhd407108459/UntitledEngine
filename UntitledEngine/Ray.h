#pragma once

#include "Collider.h"

struct Ray
{
public:
	glm::vec2 point;
	glm::vec2 direction;
};

struct Line {
public:
	glm::vec2 startPoint;
	glm::vec2 endPoint;
};

struct HitInfo
{
public:
	Collider hitCollider;
	glm::vec2 hitPoint;
};


