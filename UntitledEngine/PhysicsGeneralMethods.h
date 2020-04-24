#pragma once

#include <vector>
#include "GameComponent.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Ray.h"

namespace Physics {
	bool IsOverlapping(BoxCollider c1, BoxCollider c2);
	bool IsOverlapping(BoxCollider c1, CircleCollider c2);
	bool IsOverlapping(CircleCollider c1, CircleCollider c2);
	bool IsOverlapping(BoxCollider c1, BoxCollider c2, glm::vec2& result);
	bool IsOverlapping(BoxCollider c1, CircleCollider c2, glm::vec2& result);
	bool IsOverlapping(CircleCollider c1, CircleCollider c2, glm::vec2& result);

	bool IsTwoLineIntersecting(glm::vec2 point1, glm::vec2 point2, glm::vec2 point3, glm::vec2 point4);
	bool IsTwoLineIntersecting(glm::vec2 point1, glm::vec2 point2, glm::vec2 point3, glm::vec2 point4, glm::vec2& result);
	bool IsRayLineIntersecting(Ray ray, glm::vec2 point1, glm::vec2 point2, glm::vec2& result);
	int IsLineCircleIntersecting(glm::vec2 point, float radius, glm::vec2 point1, glm::vec2 point2, glm::vec2& result1, glm::vec2& result2);
	bool IsRayCircleIntersecting(glm::vec2 point, float radius, Ray ray, glm::vec2& result);


	glm::vec2 GetMiddlePointOfTwoMiddlePoints(glm::vec2 point1, glm::vec2 point2, glm::vec2 point3, glm::vec2 point4);
	float PointToPointDistance(float x1, float y1, float x2, float y2);
	float PointToLineDistance(float x, float y, float x1, float y1, float x2, float y2);
	float PointToInfinityLineDistance(float x, float y, float x1, float y1, float x2, float y2);
	bool IsMiddleValuesOverlapping(float v1, float v2, float v3, float v4);
	bool IsBetweenTwoValues(float v, float v1, float v2);
	bool IsInDirectionOfTwoValues(float v, float v1, float v2);
	float AngleBetweenThreePoint(float x1, float y1, float x2, float y2, float x3, float y3);
	bool IsThreePointUnclockwise(float x1, float y1, float x2, float y2, float x3, float y3);

	bool RaycastCollider(Ray ray, BoxCollider targetCollider, HitInfo& result);
	bool RaycastCollider(Ray ray, CircleCollider targetCollider, HitInfo& result);
	bool LinecastCollider(Line line, BoxCollider targetCollider, HitInfo& result);
	bool LinecastCollider(Line line, CircleCollider targetCollider, HitInfo& result);
	
	void HandleCollisionForRigidbody(Rigidbody* rb, Rigidbody* targetRb, BoxCollider* thisCollider, BoxCollider* targetCollider, glm::vec2 hitpoint);
	void HandleCollisionForRigidbody(Rigidbody* rb, Rigidbody* targetRb, CircleCollider* thisCollider, BoxCollider* targetCollider, glm::vec2 hitpoint);
	void HandleCollisionForRigidbody(Rigidbody* rb, Rigidbody* targetRb, BoxCollider* thisCollider, CircleCollider* targetCollider, glm::vec2 hitpoint);
	void HandleCollisionForRigidbody(Rigidbody* rb, Rigidbody* targetRb, CircleCollider* thisCollider, CircleCollider* targetCollider, glm::vec2 hitpoint);
}