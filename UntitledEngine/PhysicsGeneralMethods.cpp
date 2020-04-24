
#include <stdio.h>
#include "PhysicsGeneralMethods.h"
#define M_PI 3.14159265358979323846


bool Physics::IsOverlapping(BoxCollider c1, BoxCollider c2)
{
	glm::vec3 points1[4], points2[4];
	points1[0] = glm::vec3(c1.gameObject->position.x + c1.GetSize().x / 2, c1.gameObject->position.y + c1.GetSize().y / 2, 1);
	points1[1] = glm::vec3(c1.gameObject->position.x + c1.GetSize().x / 2, c1.gameObject->position.y - c1.GetSize().y / 2, 1);
	points1[2] = glm::vec3(c1.gameObject->position.x - c1.GetSize().x / 2, c1.gameObject->position.y - c1.GetSize().y / 2, 1);
	points1[3] = glm::vec3(c1.gameObject->position.x - c1.GetSize().x / 2, c1.gameObject->position.y + c1.GetSize().y / 2, 1);
	points2[0] = glm::vec3(c2.gameObject->position.x + c2.GetSize().x / 2, c2.gameObject->position.y + c2.GetSize().y / 2, 1);
	points2[1] = glm::vec3(c2.gameObject->position.x + c2.GetSize().x / 2, c2.gameObject->position.y - c2.GetSize().y / 2, 1);
	points2[2] = glm::vec3(c2.gameObject->position.x - c2.GetSize().x / 2, c2.gameObject->position.y - c2.GetSize().y / 2, 1);
	points2[3] = glm::vec3(c2.gameObject->position.x - c2.GetSize().x / 2, c2.gameObject->position.y + c2.GetSize().y / 2, 1);

	for (int i = 0; i < 4; i++) {
		points1[i] -= glm::vec3(c1.gameObject->position.x, c1.gameObject->position.y, 0);
		points2[i] -= glm::vec3(c2.gameObject->position.x, c2.gameObject->position.y, 0);
		points1[i] = c1.GetRotateMatrix() * points1[i];
		points2[i] = c2.GetRotateMatrix() * points2[i];
		points1[i] += glm::vec3(c1.gameObject->position.x, c1.gameObject->position.y, 0);
		points2[i] += glm::vec3(c2.gameObject->position.x, c2.gameObject->position.y, 0);
		glm::vec3 or1 = glm::vec3(c1.GetOffset().x, c1.GetOffset().y, 1);
		glm::vec3 or2 = glm::vec3(c2.GetOffset().x, c2.GetOffset().y, 1);
		or1 = c1.GetRotateMatrix() * or1;
		or2 = c2.GetRotateMatrix() * or2;

		points1[i] += or1;
		points2[i] += or2;
	}
	std::vector<glm::vec2> ress;
	bool flag = false;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			glm::vec2 p1, p2, p3, p4;
			int n, m;
			if (i < 3) {
				n = i + 1;
			}
			else {
				n = 0;
			}
			if (j < 3) {
				m = j + 1;
			}
			else {
				m = 0;
			}
			p1.x = points1[i].x;
			p1.y = points1[i].y;
			p2.x = points1[n].x;
			p2.y = points1[n].y;
			p3.x = points2[j].x;
			p3.y = points2[j].y;
			p4.x = points2[m].x;
			p4.y = points2[m].y;
			bool isIntersecting, isIntersecting2;
			glm::vec2 r, r2;
			isIntersecting = IsTwoLineIntersecting(p1, p2, p3, p4, r);
			if (isIntersecting) {
				flag = true;
				ress.push_back(r);
			}
			else {
				isIntersecting2 = IsTwoLineIntersecting(p3, p4, p1, p2, r2);
				if (isIntersecting2) {
					flag = true;
					ress.push_back(r2);
				}
			}
		}
	}
	if (flag) {
		return true;
	}
	else {
		return false;
	}
}

bool Physics::IsOverlapping(BoxCollider c1, CircleCollider c2)
{
	glm::vec3 points[4];
	points[0] = glm::vec3(c1.gameObject->position.x + c1.GetSize().x / 2, c1.gameObject->position.y + c1.GetSize().y / 2, 1);
	points[1] = glm::vec3(c1.gameObject->position.x + c1.GetSize().x / 2, c1.gameObject->position.y - c1.GetSize().y / 2, 1);
	points[2] = glm::vec3(c1.gameObject->position.x - c1.GetSize().x / 2, c1.gameObject->position.y - c1.GetSize().y / 2, 1);
	points[3] = glm::vec3(c1.gameObject->position.x - c1.GetSize().x / 2, c1.gameObject->position.y + c1.GetSize().y / 2, 1);
	for (int i = 0; i < 4; i++) {
		points[i] -= glm::vec3(c1.gameObject->position.x, c1.gameObject->position.y, 0);
		points[i] = c1.GetRotateMatrix() * points[i];
		points[i] += glm::vec3(c1.gameObject->position.x, c1.gameObject->position.y, 0);
		glm::vec3 or1 = glm::vec3(c1.GetOffset().x, c1.GetOffset().y, 1);
		or1 = c1.GetRotateMatrix() * or1;
		points[i] += or1;
		//printf("\nPoint%d:%f,%f\n", i, XMVectorGetX(points[i]), XMVectorGetY(points[i]));
	}
	glm::vec3 or2 = glm::vec3(c2.GetOffset().x, c2.GetOffset().y, 1);
	or2 = c2.GetRotateMatrix() * or2;
	//printf("\nPoint:%f,%f\n", XMVectorGetX(c2.GetCenter()), XMVectorGetY(c2.GetCenter()));

	std::vector<glm::vec2> ress;
	bool flag = false;
	for (int i = 0; i < 4; i++) {
		if (i < 3) {
			glm::vec2 r1, r2;
			int temp = IsLineCircleIntersecting(c2.gameObject->position, c2.GetRadius(), glm::vec2(points[i].x, points[i].y), glm::vec2(points[i + 1].x, points[i + 1].y), r1, r2);
			if (temp == 1) {
				ress.push_back(r1);
				flag = true;
			}
			else if (temp == 2) {
				ress.push_back(r1);
				ress.push_back(r2);
				flag = true;
			}
		}
		else {
			glm::vec2 r1, r2;
			int temp = IsLineCircleIntersecting(c2.gameObject->position, c2.GetRadius(), glm::vec2(points[i].x, points[i].y), glm::vec2(points[0].x, points[0].y), r1, r2);
			if (temp == 1) {
				ress.push_back(r1);
				flag = true;
			}
			else if (temp == 2) {

				ress.push_back(r1);
				ress.push_back(r2);
				flag = true;
			}
		}
	}
	if (flag) {
		return true;
	}
	else {
		return false;
	}
}

bool Physics::IsOverlapping(CircleCollider c1, CircleCollider c2)
{
	glm::vec3 or1 = glm::vec3(c1.GetOffset().x, c1.GetOffset().y, 1);
	glm::vec3 or2 = glm::vec3(c2.GetOffset().x, c2.GetOffset().y, 1);
	or1 = c1.GetRotateMatrix() * or1;
	or2 = c2.GetRotateMatrix() * or2;
	float distance = PointToPointDistance(c1.gameObject->position.x + or1.x, c1.gameObject->position.y + or1.y, c2.gameObject->position.x + or2.x, c2.gameObject->position.y + or2.y);

	if (distance <= c1.GetRadius() + c2.GetRadius()) {
		return true;
	}
	else {
		return false;
	}
}

bool Physics::IsOverlapping(BoxCollider c1, BoxCollider c2, glm::vec2& result)
{
	glm::vec3 points1[4], points2[4];
	points1[0] = glm::vec3(c1.gameObject->position.x + c1.GetSize().x / 2, c1.gameObject->position.y + c1.GetSize().y / 2, 1);
	points1[1] = glm::vec3(c1.gameObject->position.x + c1.GetSize().x / 2, c1.gameObject->position.y - c1.GetSize().y / 2, 1);
	points1[2] = glm::vec3(c1.gameObject->position.x - c1.GetSize().x / 2, c1.gameObject->position.y - c1.GetSize().y / 2, 1);
	points1[3] = glm::vec3(c1.gameObject->position.x - c1.GetSize().x / 2, c1.gameObject->position.y + c1.GetSize().y / 2, 1);
	points2[0] = glm::vec3(c2.gameObject->position.x + c2.GetSize().x / 2, c2.gameObject->position.y + c2.GetSize().y / 2, 1);
	points2[1] = glm::vec3(c2.gameObject->position.x + c2.GetSize().x / 2, c2.gameObject->position.y - c2.GetSize().y / 2, 1);
	points2[2] = glm::vec3(c2.gameObject->position.x - c2.GetSize().x / 2, c2.gameObject->position.y - c2.GetSize().y / 2, 1);
	points2[3] = glm::vec3(c2.gameObject->position.x - c2.GetSize().x / 2, c2.gameObject->position.y + c2.GetSize().y / 2, 1);


	for (int i = 0; i < 4; i++) {
		points1[i] -= glm::vec3(c1.gameObject->position.x, c1.gameObject->position.y, 0);
		points2[i] -= glm::vec3(c2.gameObject->position.x, c2.gameObject->position.y, 0);
		points1[i] = c1.GetRotateMatrix() * points1[i];
		points2[i] = c2.GetRotateMatrix() * points2[i];
		points1[i] += glm::vec3(c1.gameObject->position.x, c1.gameObject->position.y, 0);
		points2[i] += glm::vec3(c2.gameObject->position.x, c2.gameObject->position.y, 0);
		glm::vec3 or1 = glm::vec3(c1.GetOffset().x, c1.GetOffset().y, 1);
		glm::vec3 or2 = glm::vec3(c2.GetOffset().x, c2.GetOffset().y, 1);
		or1 = c1.GetRotateMatrix() * or1;
		or2 = c2.GetRotateMatrix() * or2;

		points1[i] += or1;
		points2[i] += or2;
	}


	std::vector<glm::vec2> ress;
	bool flag = false;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			glm::vec2 p1, p2, p3, p4;
			int n, m;
			if (i < 3) {
				n = i + 1;
			}
			else {
				n = 0;
			}
			if (j < 3) {
				m = j + 1;
			}
			else {
				m = 0;
			}
			p1.x = points1[i].x;
			p1.y = points1[i].y;
			p2.x = points1[n].x;
			p2.y = points1[n].y;
			p3.x = points2[j].x;
			p3.y = points2[j].y;
			p4.x = points2[m].x;
			p4.y = points2[m].y;
			bool isIntersecting, isIntersecting2;
			glm::vec2 r,r2;
			isIntersecting = IsTwoLineIntersecting(p1, p2, p3, p4, r);
			if (isIntersecting) {
				flag = true;
				ress.push_back(r);
			}
			else {
				isIntersecting2 = IsTwoLineIntersecting(p3, p4, p1, p2, r2);
				if (isIntersecting2) {
					flag = true;
					ress.push_back(r2);
				}
			}
		}
	}
	if (flag) {
		glm::vec2 r;
		r.x = 0;
		r.y = 0;
		for (int i = 0; i < ress.size(); i++) {
			r.x += ress[i].x;
			r.y += ress[i].y;
		}
		r.x /= ress.size();
		r.y /= ress.size();
		result = r;
		return true;
	}
	else {
		return false;
	}
}

bool Physics::IsOverlapping(BoxCollider c1, CircleCollider c2, glm::vec2& result)
{
	glm::vec3 points[4];
	points[0] = glm::vec3(c1.gameObject->position.x + c1.GetSize().x / 2, c1.gameObject->position.y + c1.GetSize().y / 2, 1);
	points[1] = glm::vec3(c1.gameObject->position.x + c1.GetSize().x / 2, c1.gameObject->position.y - c1.GetSize().y / 2, 1);
	points[2] = glm::vec3(c1.gameObject->position.x - c1.GetSize().x / 2, c1.gameObject->position.y - c1.GetSize().y / 2, 1);
	points[3] = glm::vec3(c1.gameObject->position.x - c1.GetSize().x / 2, c1.gameObject->position.y + c1.GetSize().y / 2, 1);
	for (int i = 0; i < 4; i++) {
		points[i] -= glm::vec3(c1.gameObject->position.x, c1.gameObject->position.y, 0);
		points[i] = c1.GetRotateMatrix() * points[i];
		points[i] += glm::vec3(c1.gameObject->position.x, c1.gameObject->position.y, 0);
		glm::vec3 or1 = glm::vec3(c1.GetOffset().x, c1.GetOffset().y, 1);
		or1 = c1.GetRotateMatrix() * or1;
		points[i] += or1;
		//printf("\nPoint%d:%f,%f\n", i, XMVectorGetX(points[i]), XMVectorGetY(points[i]));
	}
	glm::vec3 or2 = glm::vec3(c2.GetOffset().x, c2.GetOffset().y, 1);
	or2 = c2.GetRotateMatrix() * or2;
	//printf("\nPoint:%f,%f\n", XMVectorGetX(c2.GetCenter()), XMVectorGetY(c2.GetCenter()));

	std::vector<glm::vec2> ress;
	bool flag = false;
	for (int i = 0; i < 4; i++) {
		if (i < 3) {
			glm::vec2 r1, r2;
			int temp = IsLineCircleIntersecting(c2.gameObject->position, c2.GetRadius(), glm::vec2(points[i].x, points[i].y), glm::vec2(points[i + 1].x, points[i + 1].y), r1, r2);
			if (temp == 1) {
				ress.push_back(r1);
				flag = true;
			}
			else if (temp == 2) {
				ress.push_back(r1);
				ress.push_back(r2);
				flag = true;
			}
		}
		else {
			glm::vec2 r1, r2;
			int temp = IsLineCircleIntersecting(c2.gameObject->position, c2.GetRadius(), glm::vec2(points[i].x, points[i].y), glm::vec2(points[0].x, points[0].y), r1, r2);
			if (temp == 1) {
				ress.push_back(r1);
				flag = true;
			}
			else if (temp == 2) {

				ress.push_back(r1);
				ress.push_back(r2);
				flag = true;
			}
		}
	}
	if (flag) {
		glm::vec2 r;
		r.x = 0;
		r.y = 0;
		for (int i = 0; i < ress.size(); i++) {
			r.x += ress[i].x;
			r.y += ress[i].y;
			//printf("\nPoint:%f,%f\n", ress[i].x, ress[i].y);
		}
		r.x /= ress.size();
		r.y /= ress.size();
		result = r;

		//printf("\nPoint:%f,%f\n", XMVectorGetX(result), XMVectorGetY(result));
		return true;
	}
	else {
		return false;
	}
}

bool Physics::IsOverlapping(CircleCollider c1, CircleCollider c2, glm::vec2& result)
{
	glm::vec3 or1 = glm::vec3(c1.GetOffset().x, c1.GetOffset().y, 1);
	glm::vec3 or2 = glm::vec3(c2.GetOffset().x, c2.GetOffset().y, 1);
	or1 = c1.GetRotateMatrix() * or1;
	or2 = c2.GetRotateMatrix() * or2;
	float distance = PointToPointDistance(c1.gameObject->position.x + or1.x, c1.gameObject->position.y + or1.y, c2.gameObject->position.x + or2.x, c2.gameObject->position.y + or2.y);

	if (distance <= c1.GetRadius() + c2.GetRadius()) {
		float r1 = c1.GetRadius() / (c1.GetRadius() + c2.GetRadius());
		float r2 = c2.GetRadius() / (c1.GetRadius() + c2.GetRadius());
		result = r2 * (c1.gameObject->position + glm::vec2(or1.x, or1.y)) + r1 * (c2.gameObject->position + glm::vec2(or2.x, or2.y));
		return true;
	}
	else {
		return false;
	}
}

bool Physics::IsTwoLineIntersecting(glm::vec2 point1, glm::vec2 point2, glm::vec2 point3, glm::vec2 point4)
{
	bool isPerp1 = false, isPerp2 = false;
	double k1, b1, k2, b2;
	if (point2.x != point1.x) {
		k1 = (point2.y - point1.y) / (point2.x - point1.x);
		b1 = point1.y - k1 * point1.x;
	}
	else {
		isPerp1 = true;
	}
	if (point4.x != point3.x) {
		k2 = (point4.y - point3.y) / (point4.x - point3.x);
		b2 = point3.y - k2 * point3.x;
	}
	else {
		isPerp2 = true;
	}
	if (!isPerp1 && !isPerp2) {
		if (k1 == k2) {
			if (b1 == b2) {
				if (IsMiddleValuesOverlapping(point1.x, point2.x, point3.x, point4.x)) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		float px = (b2 - b1) / (k1 - k2);
		float py = k1 * px + b1;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsBetweenTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsBetweenTwoValues(py, point3.y, point4.y)) {
			return true;
		}
		else {
			return false;
		}
		return true;
	}
	else if (isPerp1 && isPerp2) {
		if (point1.x == point3.x) {
			if (IsMiddleValuesOverlapping(point1.y, point2.y, point3.y, point4.y)) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else if (isPerp1 && !isPerp2) {
		float px = point1.x;
		float py = k2 * px + b2;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsBetweenTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsBetweenTwoValues(py, point3.y, point4.y)) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (!isPerp1 && isPerp2) {
		float px = point3.x;
		float py = k1 * px + b1;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsBetweenTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsBetweenTwoValues(py, point3.y, point4.y)) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

bool Physics::IsTwoLineIntersecting(glm::vec2 point1, glm::vec2 point2, glm::vec2 point3, glm::vec2 point4, glm::vec2& result)
{
	bool isPerp1 = false, isPerp2 = false;
	double k1, b1, k2, b2;
	if (point2.x != point1.x) {
		k1 = (point2.y - point1.y) / (point2.x - point1.x);
		b1 = point1.y - k1 * point1.x;
	}
	else {
		isPerp1 = true;
	}
	if (point4.x != point3.x) {
		k2 = (point4.y - point3.y) / (point4.x - point3.x);
		b2 = point3.y - k2 * point3.x;
	}
	else {
		isPerp2 = true;
	}
	if (!isPerp1 && !isPerp2) {
		if (k1 == k2) {
			if (b1 == b2) {
				if (IsMiddleValuesOverlapping(point1.x, point2.x, point3.x, point4.x)) {
					result = GetMiddlePointOfTwoMiddlePoints(point1, point2, point3, point4);
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		float px = (b2 - b1) / (k1 - k2);
		float py = k1 * px + b1;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsBetweenTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsBetweenTwoValues(py, point3.y, point4.y)) {
			result.x = px;
			result.y = py;
			return true;
		}
		else {
			return false;
		}
		return true;
	}
	else if (isPerp1 && isPerp2) {
		if (point1.x == point3.x) {
			if (IsMiddleValuesOverlapping(point1.y, point2.y, point3.y, point4.y)) {
				result = GetMiddlePointOfTwoMiddlePoints(point1, point2, point3, point4);
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else if (isPerp1 && !isPerp2) {
		float px = point1.x;
		float py = k2 * px + b2;
		if (IsBetweenTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsBetweenTwoValues(py, point3.y, point4.y)) {
			result.x = px;
			result.y = py;
			return true;
		}
		else {
			return false;
		}
	}
	else if (!isPerp1 && isPerp2) {
		float px = point3.x;
		float py = k1 * px + b1;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsBetweenTwoValues(py, point3.y, point4.y)) {
			result.x = px;
			result.y = py;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

bool Physics::IsRayLineIntersecting(Ray ray, glm::vec2 point1, glm::vec2 point2, glm::vec2& result)
{
	bool isPerp1 = false, isPerp2 = false;
	double k1, b1, k2, b2;
	glm::vec2 point3 = glm::vec2(ray.point.x, ray.point.y);
	glm::vec2 point4 = glm::vec2(ray.point.x + ray.direction.x, ray.point.y + ray.direction.y);
	if (point2.x != point1.x) {
		k1 = (point2.y - point1.y) / (point2.x - point1.x);
		b1 = point1.y - k1 * point1.x;
	}
	else {
		isPerp1 = true;
	}
	if (point4.x != point3.x) {
		k2 = (point4.y - point3.y) / (point4.x - point3.x);
		b2 = point3.y - k2 * point3.x;
	}
	else {
		isPerp2 = true;
	}
	if (!isPerp1 && !isPerp2) {
		if (k1 == k2) {
			if (b1 == b2) {
				if (IsMiddleValuesOverlapping(point1.x, point2.x, point3.x, point4.x)) {
					result = GetMiddlePointOfTwoMiddlePoints(point1, point2, point3, point4);
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		float px = (b2 - b1) / (k1 - k2);
		float py = k1 * px + b1;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsInDirectionOfTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsInDirectionOfTwoValues(py, point3.y, point4.y)) {
			result.x = px;
			result.y = py;
			return true;
		}
		else {
			return false;
		}
		return true;
	}
	else if (isPerp1 && isPerp2) {
		if (point1.x == point3.x) {
			if (point4.y - point3.y > 0) {
				if (point1.y > point3.y && point2.y > point3.y) {
					if (point1.y > point2.y) {
						result = point2;
					}
					else {
						result = point1;
					}
					return true;
				}
				else if (point1.y > point3.y) {
					result = point1;
					return true;
				}
				else if (point2.y > point3.y) {
					result = point2;
					return true;
				}
				else {
					return false;
				}
			}
			else {
				if (point1.y < point3.y && point2.y < point3.y) {
					if (point1.y < point2.y) {
						result = point2;
					}
					else {
						result = point1;
					}
					return true;
				}
				else if (point1.y < point3.y) {
					result = point1;
					return true;
				}
				else if (point2.y < point3.y) {
					result = point2;
					return true;
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
	else if (isPerp1 && !isPerp2) {
		float px = point1.x;
		float py = k2 * px + b2;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsInDirectionOfTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsInDirectionOfTwoValues(py, point3.y, point4.y)) {
			result.x = px;
			result.y = py;
			return true;
		}
		else {
			return false;
		}
	}
	else if (!isPerp1 && isPerp2) {
		float px = point3.x;
		float py = k1 * px + b1;
		if (IsBetweenTwoValues(px, point1.x, point2.x) && IsInDirectionOfTwoValues(px, point3.x, point4.x) && IsBetweenTwoValues(py, point1.y, point2.y) && IsInDirectionOfTwoValues(py, point3.y, point4.y)) {
			result.x = px;
			result.y = py;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

int Physics::IsLineCircleIntersecting(glm::vec2 point, float radius, glm::vec2 point1, glm::vec2 point2, glm::vec2& result1, glm::vec2& result2)
{
	if (PointToLineDistance(point.x, point.y, point1.x, point1.y, point2.x, point2.y) > radius) {
		return 0;
	}
	float a, b, c, n, u1, u2;
	a = (point2.x - point1.x) * (point2.x - point1.x) + (point2.y - point1.y) * (point2.y - point1.y);
	b = 2 * ((point2.x - point1.x) * (point1.x - point.x) + (point2.y - point1.y) * (point1.y - point.y));
	c = point.x * point.x + point.y * point.y + point1.x * point1.x + point1.y * point1.y - 2 * (point.x * point1.x + point.y * point1.y) - radius * radius;
	n = b * b - 4 * a * c;
	if (n < 0) {
		return 0;
	}
	else if (n == 0) {
		u1 = (-b + sqrtf(n)) / (2 * a);
		if (u1 > 0 && u1 < 1) {

			result1.x = point1.x + u1 * (point2.x - point1.x);
			result1.y = point1.y + u1 * (point2.y - point1.y);
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		u1 = (-b + sqrtf(n)) / (2 * a);
		u2 = (-b - sqrtf(n)) / (2 * a);

		if (u1 > 0 && u1 < 1 && u2 >0 && u2 < 1) {
			result1.x = point1.x + u1 * (point2.x - point1.x);
			result1.y = point1.y + u1 * (point2.y - point1.y);
			//printf("\nPoint:%f,%f\n", result1.x, result1.y);


			result2.x = point1.x + u2 * (point2.x - point1.x);
			result2.y = point1.y + u2 * (point2.y - point1.y);
			//printf("\nPoint:%f,%f\n", result2.x, result2.y);


			return 2;
		}
		else if (u1 > 0 && u1 < 1) {
			result1.x = point1.x + u1 * (point2.x - point1.x);
			result1.y = point1.y + u1 * (point2.y - point1.y);
			return 1;
		}
		else if (u2 > 0 && u2 < 1) {
			result1.x = point1.x + u2 * (point2.x - point1.x);
			result1.y = point1.y + u2 * (point2.y - point1.y);
			return 1;
		}
		else {
			return 0;
		}
	}
	return 0;
}

bool Physics::IsRayCircleIntersecting(glm::vec2 point, float radius, Ray ray, glm::vec2& result)
{
	glm::vec2 point1, point2;
	point1.x = ray.point.x;
	point1.y = ray.point.y;
	point2.x = ray.point.x + ray.direction.x;
	point2.y = ray.point.y + ray.direction.y;
	if (PointToInfinityLineDistance(point.x, point.y, point1.x, point1.y, point2.x, point2.y) > radius) {
		return false;
	}
	float a, b, c, n, u1, u2;
	a = (point2.x - point1.x) * (point2.x - point1.x) + (point2.y - point1.y) * (point2.y - point1.y);
	b = 2 * ((point2.x - point1.x) * (point1.x - point.x) + (point2.y - point1.y) * (point1.y - point.y));
	c = point.x * point.x + point.y * point.y + point1.x * point1.x + point1.y * point1.y - 2 * (point.x * point1.x + point.y * point1.y) - radius * radius;
	n = b * b - 4 * a * c;
	if (n < 0) {
		return false;
	}
	else if (n == 0) {
		glm::vec2 temp;
		u1 = (-b + sqrtf(n)) / (2 * a);
		temp.x = point1.x + u1 * (point2.x - point1.x);
		temp.y = point1.y + u1 * (point2.y - point1.y);
		if (IsInDirectionOfTwoValues(temp.x, point1.x, point2.x) && IsInDirectionOfTwoValues(temp.y, point1.y, point2.y)) {
			result = temp;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		u1 = (-b + sqrtf(n)) / (2 * a);
		u2 = (-b - sqrtf(n)) / (2 * a);
		glm::vec2 temp1, temp2;
		temp1.x = point1.x + u1 * (point2.x - point1.x);
		temp1.y = point1.y + u1 * (point2.y - point1.y);

		temp2.x = point1.x + u2 * (point2.x - point1.x);
		temp2.y = point1.y + u2 * (point2.y - point1.y);
		bool isT1, isT2;
		isT1 = IsInDirectionOfTwoValues(temp1.x, point1.x, point2.x) && IsInDirectionOfTwoValues(temp1.y, point1.y, point2.y);
		isT2 = IsInDirectionOfTwoValues(temp2.x, point1.x, point2.x) && IsInDirectionOfTwoValues(temp2.y, point1.y, point2.y);
		if (isT1 && isT2) {
			float d1, d2;
			d1 = PointToPointDistance(temp1.x, temp1.y, point1.x, point1.y);
			d2 = PointToPointDistance(temp2.x, temp2.y, point1.x, point1.y);

			if (d1 < d2) {
				result = temp1;
				return true;
			}
			else {
				result = temp2;
				return true;
			}
		}
		else if (isT1) {
			result = temp1;
			return true;
		}
		else if (isT2) {
			result = temp2;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

glm::vec2 Physics::GetMiddlePointOfTwoMiddlePoints(glm::vec2 point1, glm::vec2 point2, glm::vec2 point3, glm::vec2 point4)
{
	float x[4], y[4];
	x[0] = point1.x;
	x[1] = point2.x;
	x[2] = point3.x;
	x[3] = point4.x;
	y[0] = point1.y;
	y[1] = point2.y;
	y[2] = point3.y;
	y[3] = point4.y;
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {
			if (x[i] > x[j]) {
				float temp;
				temp = x[i];
				x[i] = x[j];
				x[j] = temp;
			}
			if (y[i] > y[j]) {
				float temp;
				temp = y[i];
				y[i] = y[j];
				y[j] = temp;
			}
		}
	}
	glm::vec2 point;
	point.x = (x[1] + x[2]) / 2;
	point.y = (y[1] + y[2]) / 2;
	return point;
}

float Physics::PointToPointDistance(float x1, float y1, float x2, float y2)
{
	return sqrtf(powf((x2 - x1), 2) + powf((y2 - y1), 2));
}

float Physics::PointToLineDistance(float x, float y, float x1, float y1, float x2, float y2)
{

	/*float cross = (x2 - x1) * (x - x1) + (y2 - y1) * (y - y1);
	if (cross <= 0) {
		return sqrtf((x - x1) * (x - x1) + (y - y1) * (y - y1));
	}

	float d2 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
	if (cross >= d2) {
		return sqrtf((x - x2) * (x - x2) + (y - y2) * (y - y2));
	}

	float r = cross / d2;
	float px = x1 + (x2 - x1) * r;
	float py = y1 + (y2 - y1) * r;
	return sqrtf((x - px) * (x - px) + (py - y1) * (py - y1));*/
	float a, b, c;
	a = PointToPointDistance(x2, y2, x, y);
	if (a <= 0.00001f) {
		return 0.0f;
	}

	b = PointToPointDistance(x1, y1, x, y);
	if (b <= 0.00001f) {
		return 0.0f;
	}

	c = PointToPointDistance(x1, y1, x2, y2);
	if (c <= 0.00001f) {
		return a;
	}

	if (a * a >= b * b + c * c) {
		return b;
	}
	if (b * b >= a * a + c * c) {
		return a;
	}

	float l = (a + b + c) / 2;
	float s = sqrt(l * (l - a) * (l - b) * (l - c));
	return 2 * s / c;
}

float Physics::PointToInfinityLineDistance(float x, float y, float x1, float y1, float x2, float y2)
{
	float a, b, c;
	a = PointToPointDistance(x2, y2, x, y);
	if (a <= 0.00001f) {
		return 0.0f;
	}

	b = PointToPointDistance(x1, y1, x, y);
	if (b <= 0.00001f) {
		return 0.0f;
	}

	c = PointToPointDistance(x1, y1, x2, y2);
	if (c <= 0.00001f) {
		return a;
	}

	float l = (a + b + c) / 2;
	float s = sqrt(l * (l - a) * (l - b) * (l - c));
	return 2 * s / c;
}

bool Physics::IsMiddleValuesOverlapping(float v1, float v2, float v3, float v4)
{
	if (v1 < v3 && v1 < v4 && v2 < v3 && v2 < v4) {
		return false;
	}
	if (v3 < v1 && v3 < v2 && v4 < v1 && v4 < v2) {
		return false;
	}
	return true;
}

bool Physics::IsBetweenTwoValues(float v, float v1, float v2)
{
	if (v1 < v2) {
		if (v >= v1 && v <= v2) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (v >= v2 && v <= v1) {
			return true;
		}
		else {
			return false;
		}
	}
}

bool Physics::IsInDirectionOfTwoValues(float v, float v1, float v2)
{
	if (v1 > v2) {
		if (v >= v1) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (v <= v1) {
			return true;
		}
		else {
			return false;
		}
	}
}

float Physics::AngleBetweenThreePoint(float x1, float y1, float x2, float y2, float x3, float y3)
{
	float la, lb, lc;
	la = PointToPointDistance(x1, y1, x2, y2);
	lb = PointToPointDistance(x2, y2, x3, y3);
	lc = PointToPointDistance(x1, y1, x3, y3);
	float cos = (la * la + lb * lb - lc * lc) / (2 * la * lb);
	float angle = acosf(cos);
	return angle;
}

bool Physics::IsThreePointUnclockwise(float x1, float y1, float x2, float y2, float x3, float y3)
{
	float ans = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
	if (ans > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Physics::RaycastCollider(Ray ray, BoxCollider targetCollider, HitInfo& result)
{
	glm::vec3 points[4];
	points[0] = glm::vec3(targetCollider.gameObject->position.x + targetCollider.GetSize().x / 2, targetCollider.gameObject->position.y + targetCollider.GetSize().y / 2, 1);
	points[1] = glm::vec3(targetCollider.gameObject->position.x + targetCollider.GetSize().x / 2, targetCollider.gameObject->position.y - targetCollider.GetSize().y / 2, 1);
	points[2] = glm::vec3(targetCollider.gameObject->position.x - targetCollider.GetSize().x / 2, targetCollider.gameObject->position.y - targetCollider.GetSize().y / 2, 1);
	points[3] = glm::vec3(targetCollider.gameObject->position.x - targetCollider.GetSize().x / 2, targetCollider.gameObject->position.y + targetCollider.GetSize().y / 2, 1);
	for (int i = 0; i < 4; i++) {
		points[i] -= glm::vec3(targetCollider.gameObject->position.x, targetCollider.gameObject->position.y, 0);
		points[i] = targetCollider.GetRotateMatrix() * points[i];
		points[i] += glm::vec3(targetCollider.gameObject->position.x, targetCollider.gameObject->position.y, 0);
		glm::vec3 or1 = glm::vec3(targetCollider.GetOffset().x, targetCollider.GetOffset().y, 1);
		or1 = targetCollider.GetRotateMatrix() * or1;
		points[i] += or1;
	}
	std::vector<glm::vec2> ress;
	bool isHitted = false;
	for (int i = 0; i < 4; i++) {
		glm::vec2 r;
		if (i < 3) {
			if (IsRayLineIntersecting(ray, glm::vec2(points[i].x, points[i].y), glm::vec2(points[i + 1].x, points[i + 1].y), r)) {
				isHitted = true;
				ress.push_back(r);
			}
		}
		else {
			if (IsRayLineIntersecting(ray, glm::vec2(points[i].x, points[i].y), glm::vec2(points[0].x, points[0].y), r)) {
				isHitted = true;
				ress.push_back(r);
			}
		}
	}
	if (isHitted) {
		result.hitCollider = targetCollider;
		int minIndex = 0;
		float minDis = PointToPointDistance(ress[0].x, ress[0].y, ray.point.x, ray.point.y);
		for (int i = 0; i < ress.size(); i++) {
			float dis = PointToPointDistance(ress[i].x, ress[i].y, ray.point.x, ray.point.y);
			if (dis < minDis) {
				minDis = dis;
				minIndex = i;
			}
		}
		glm::vec2 re;
		re = ress[minIndex];
		result.hitPoint = re;
		return true;
	}
	else {
		return false;
	}
}

bool Physics::RaycastCollider(Ray ray, CircleCollider targetCollider, HitInfo& result)
{
	glm::vec2 point;
	glm::vec3 or1 = glm::vec3(targetCollider.GetOffset().x, targetCollider.GetOffset().y, 1);;
	or1 = targetCollider.GetRotateMatrix() * or1 ;
	point.x = targetCollider.gameObject->position.x + or1.x;
	point.y = targetCollider.gameObject->position.y + or1.y;

	glm::vec2 r;
	if (IsRayCircleIntersecting(point, targetCollider.GetRadius(), ray, r)) {
		result.hitCollider = targetCollider;
		result.hitPoint = r;
		return true;
	}
	else {
		return false;
	}
}

bool Physics::LinecastCollider(Line line, BoxCollider targetCollider, HitInfo& result)
{
	glm::vec3 points[4];
	points[0] = glm::vec3(targetCollider.gameObject->position.x + targetCollider.GetSize().x / 2, targetCollider.gameObject->position.y + targetCollider.GetSize().y / 2, 1);
	points[1] = glm::vec3(targetCollider.gameObject->position.x + targetCollider.GetSize().x / 2, targetCollider.gameObject->position.y - targetCollider.GetSize().y / 2, 1);
	points[2] = glm::vec3(targetCollider.gameObject->position.x - targetCollider.GetSize().x / 2, targetCollider.gameObject->position.y - targetCollider.GetSize().y / 2, 1);
	points[3] = glm::vec3(targetCollider.gameObject->position.x - targetCollider.GetSize().x / 2, targetCollider.gameObject->position.y + targetCollider.GetSize().y / 2, 1);
	for (int i = 0; i < 4; i++) {
		points[i] -= glm::vec3(targetCollider.gameObject->position.x, targetCollider.gameObject->position.y, 0);
		points[i] = targetCollider.GetRotateMatrix() * points[i];
		points[i] += glm::vec3(targetCollider.gameObject->position.x, targetCollider.gameObject->position.y, 0);
		glm::vec3 or1 = glm::vec3(targetCollider.GetOffset().x, targetCollider.GetOffset().y, 1);
		or1 = targetCollider.GetRotateMatrix() * or1;
		points[i] += or1;
	}
	std::vector<glm::vec2> ress;
	bool isHitted = false;
	for (int i = 0; i < 4; i++) {
		glm::vec2 r;
		if (i < 3) {
			if (IsTwoLineIntersecting(line.startPoint, line.endPoint, glm::vec2(points[i].x, points[i].y), glm::vec2(points[i + 1].x, points[i + 1].y), r)) {
				isHitted = true;
				ress.push_back(r);
			}
		}
		else {
			if (IsTwoLineIntersecting(line.startPoint, line.endPoint, glm::vec2(points[i].x, points[i].y), glm::vec2(points[0].x, points[0].y), r)) {
				isHitted = true;
				ress.push_back(r);
			}
		}
	}
	if (isHitted) {
		result.hitCollider = targetCollider;
		int minIndex = 0;
		float minDis = PointToPointDistance(ress[0].x, ress[0].y, line.startPoint.x, line.startPoint.y);
		for (int i = 0; i < ress.size(); i++) {
			float dis = PointToPointDistance(ress[i].x, ress[i].y, line.startPoint.x, line.startPoint.y);
			if (dis < minDis) {
				minDis = dis;
				minIndex = i;
			}
		}
		glm::vec2 re;
		re = ress[minIndex];
		result.hitPoint = re;
		return true;
	}
	else {
		return false;
	}
}

bool Physics::LinecastCollider(Line line, CircleCollider targetCollider, HitInfo& result)
{
	glm::vec2 point;
	glm::vec3 or1 = glm::vec3(targetCollider.GetOffset().x, targetCollider.GetOffset().y, 1);;
	or1 = targetCollider.GetRotateMatrix() * or1;
	point.x = targetCollider.gameObject->position.x + or1.x;
	point.y = targetCollider.gameObject->position.y + or1.y;

	glm::vec2 r1, r2;
	int isIntersecting = IsLineCircleIntersecting(point, targetCollider.GetRadius(), line.startPoint, line.endPoint, r1, r2);
	if (isIntersecting == 0) {
		return false;
	}
	else if (isIntersecting == 1) {
		result.hitCollider = targetCollider;
		result.hitPoint = r1;
		return true;
	}
	else {
		if (PointToPointDistance(r1.x, r1.y, line.startPoint.x, line.startPoint.y) > PointToPointDistance(r2.x, r2.y, line.startPoint.x, line.startPoint.y)) {
			result.hitCollider = targetCollider;
			result.hitPoint = r1;
			return true;
		}
		else {
			result.hitCollider = targetCollider;
			result.hitPoint = r2;
			return true;
		}
	}
	
}

void Physics::HandleCollisionForRigidbody(Rigidbody* rb, Rigidbody* targetRb, BoxCollider* thisCollider, BoxCollider* targetCollider, glm::vec2 hitpoint)
{
	glm::vec3 or1 = glm::vec3(thisCollider->GetOffset().x, thisCollider->GetOffset().y, 1);
	or1 = thisCollider->GetRotateMatrix() * or1;

	Ray ray;
	ray.point = thisCollider->gameObject->position + glm::vec2(or1.x,or1.y);
	ray.direction = ray.point - hitpoint;

	/*Ray ray2;
	ray2.point = hitpoint;
	ray2.direction = ray2.point - (targetCollider->GetCenter() + or1);*/


	HitInfo hit1;//hit2;
	bool t1 = RaycastCollider(ray, *thisCollider, hit1);
	//bool t2 = RaycastCollider(ray, *targetCollider, hit2);
	if (!t1) {
		hit1.hitPoint = hitpoint;
	}
	/*if (!t2) {
		hit2.hitPoint = hitpoint;
	}*/
	glm::vec2 delta = hit1.hitPoint - hitpoint;
	//float dis = sqrtf(XMVectorGetX(delta) * XMVectorGetX(delta) + XMVectorGetY(delta) * XMVectorGetY(delta));
	//if (dis > PointToPointDistance(XMVectorGetX(thisCollider->GetCenter()), XMVectorGetY(thisCollider->GetCenter()), XMVectorGetX(targetCollider->GetCenter()), XMVectorGetY(targetCollider->GetCenter()))) {
	//	//printf("%f\n", dis);
	//	return;
	//}
	//printf("delta: %f,%f\n", XMVectorGetX(hitpoint), XMVectorGetY(hitpoint));
	//printf("delta: %f,%f\n", XMVectorGetX(ray.point), XMVectorGetY(ray.point));
	if (!rb->isStatic && !rb->isLockPosition) {
		thisCollider->gameObject->position -= delta;
	}
	if (!targetRb->isStatic && !targetRb->isLockPosition) {
		targetCollider->gameObject->position += delta;
	}
	if (rb->isLockPosition && targetRb->isLockPosition) {
		thisCollider->gameObject->position -= delta;
		targetCollider->gameObject->position += delta;
	}
	if (rb->isStatic || targetRb->isStatic) {
		return;
	}
	//printf("hit1: %f,%f\n", XMVectorGetX(hit1.hitPoint), XMVectorGetY(hit1.hitPoint));
	//printf("hit2: %f,%f\n", XMVectorGetX(hit2.hitPoint), XMVectorGetY(hit2.hitPoint));
	float f = targetRb->mass * powf(targetRb->angularVelocity * M_PI / 180, 2) * (PointToPointDistance(hitpoint.x, hitpoint.y, targetCollider->gameObject->position.x, targetCollider->gameObject->position.y));
	glm::vec2 force = glm::normalize(thisCollider->gameObject->position - hitpoint) * f;
	float f2 = rb->mass * powf(rb->angularVelocity * M_PI / 180, 2) * (PointToPointDistance(hitpoint.x, hitpoint.y, thisCollider->gameObject->position.x, thisCollider->gameObject->position.y));
	glm::vec2 force2 = glm::normalize(targetCollider->gameObject->position - hitpoint) * f;
	//printf("force: %f, %f, %f ,%f\n", f, XMVectorGetX(force), XMVectorGetY(force), XMVectorGetZ(force));
	targetRb->AddForceAtPoint(rb->velocity - force, hitpoint);
	rb->AddForceAtPoint(targetRb->velocity - force, hitpoint);
}

void Physics::HandleCollisionForRigidbody(Rigidbody* rb, Rigidbody* targetRb, CircleCollider* thisCollider, BoxCollider* targetCollider, glm::vec2 hitpoint)
{
	glm::vec3 or1 = glm::vec3(thisCollider->GetOffset().x, thisCollider->GetOffset().y, 1);
	or1 = thisCollider->GetRotateMatrix() * or1;

	Ray ray;
	ray.point = thisCollider->gameObject->position + glm::vec2(or1.x, or1.y);
	ray.direction = ray.point - hitpoint;

	/*Ray ray2;
	ray2.point = hitpoint;
	ray2.direction = ray2.point - (targetCollider->GetCenter() + or1);*/


	HitInfo hit1;//hit2;
	bool t1 = RaycastCollider(ray, *thisCollider, hit1);
	//bool t2 = RaycastCollider(ray, *targetCollider, hit2);
	if (!t1) {
		hit1.hitPoint = hitpoint;
	}
	/*if (!t2) {
		hit2.hitPoint = hitpoint;
	}*/
	glm::vec2 delta = hit1.hitPoint - hitpoint;
	//float dis = sqrtf(XMVectorGetX(delta) * XMVectorGetX(delta) + XMVectorGetY(delta) * XMVectorGetY(delta));
	//if (dis > PointToPointDistance(XMVectorGetX(thisCollider->GetCenter()), XMVectorGetY(thisCollider->GetCenter()), XMVectorGetX(targetCollider->GetCenter()), XMVectorGetY(targetCollider->GetCenter()))) {
	//	//printf("%f\n", dis);
	//	return;
	//}
	//printf("delta: %f,%f\n", XMVectorGetX(hitpoint), XMVectorGetY(hitpoint));
	//printf("delta: %f,%f\n", XMVectorGetX(ray.point), XMVectorGetY(ray.point));
	if (!rb->isStatic && !rb->isLockPosition) {
		thisCollider->gameObject->position -= delta;
	}
	if (!targetRb->isStatic && !targetRb->isLockPosition) {
		targetCollider->gameObject->position += delta;
	}
	if (rb->isLockPosition && targetRb->isLockPosition) {
		thisCollider->gameObject->position -= delta;
		targetCollider->gameObject->position += delta;
	}
	if (rb->isStatic || targetRb->isStatic) {
		return;
	}
	//printf("hit1: %f,%f\n", XMVectorGetX(hit1.hitPoint), XMVectorGetY(hit1.hitPoint));
	//printf("hit2: %f,%f\n", XMVectorGetX(hit2.hitPoint), XMVectorGetY(hit2.hitPoint));
	float f = targetRb->mass * powf(targetRb->angularVelocity * M_PI / 180, 2) * (PointToPointDistance(hitpoint.x, hitpoint.y, targetCollider->gameObject->position.x, targetCollider->gameObject->position.y));
	glm::vec2 force = glm::normalize(thisCollider->gameObject->position - hitpoint) * f;
	float f2 = rb->mass * powf(rb->angularVelocity * M_PI / 180, 2) * (PointToPointDistance(hitpoint.x, hitpoint.y, thisCollider->gameObject->position.x, thisCollider->gameObject->position.y));
	glm::vec2 force2 = glm::normalize(targetCollider->gameObject->position - hitpoint) * f;
	//printf("force: %f, %f, %f ,%f\n", f, XMVectorGetX(force), XMVectorGetY(force), XMVectorGetZ(force));
	targetRb->AddForceAtPoint(rb->velocity - force, hitpoint);
	rb->AddForceAtPoint(targetRb->velocity - force, hitpoint);
}

void Physics::HandleCollisionForRigidbody(Rigidbody* rb, Rigidbody* targetRb, BoxCollider* thisCollider, CircleCollider* targetCollider, glm::vec2 hitpoint)
{
	glm::vec3 or1 = glm::vec3(thisCollider->GetOffset().x, thisCollider->GetOffset().y, 1);
	or1 = thisCollider->GetRotateMatrix() * or1;

	Ray ray;
	ray.point = thisCollider->gameObject->position + glm::vec2(or1.x, or1.y);
	ray.direction = ray.point - hitpoint;

	/*Ray ray2;
	ray2.point = hitpoint;
	ray2.direction = ray2.point - (targetCollider->GetCenter() + or1);*/


	HitInfo hit1;//hit2;
	bool t1 = RaycastCollider(ray, *thisCollider, hit1);
	//bool t2 = RaycastCollider(ray, *targetCollider, hit2);
	if (!t1) {
		hit1.hitPoint = hitpoint;
	}
	/*if (!t2) {
		hit2.hitPoint = hitpoint;
	}*/
	glm::vec2 delta = hit1.hitPoint - hitpoint;
	//float dis = sqrtf(XMVectorGetX(delta) * XMVectorGetX(delta) + XMVectorGetY(delta) * XMVectorGetY(delta));
	//if (dis > PointToPointDistance(XMVectorGetX(thisCollider->GetCenter()), XMVectorGetY(thisCollider->GetCenter()), XMVectorGetX(targetCollider->GetCenter()), XMVectorGetY(targetCollider->GetCenter()))) {
	//	//printf("%f\n", dis);
	//	return;
	//}
	//printf("delta: %f,%f\n", XMVectorGetX(hitpoint), XMVectorGetY(hitpoint));
	//printf("delta: %f,%f\n", XMVectorGetX(ray.point), XMVectorGetY(ray.point));
	if (!rb->isStatic && !rb->isLockPosition) {
		thisCollider->gameObject->position -= delta;
	}
	if (!targetRb->isStatic && !targetRb->isLockPosition) {
		targetCollider->gameObject->position += delta;
	}
	if (rb->isLockPosition && targetRb->isLockPosition) {
		thisCollider->gameObject->position -= delta;
		targetCollider->gameObject->position += delta;
	}
	if (rb->isStatic || targetRb->isStatic) {
		return;
	}
	//printf("hit1: %f,%f\n", XMVectorGetX(hit1.hitPoint), XMVectorGetY(hit1.hitPoint));
	//printf("hit2: %f,%f\n", XMVectorGetX(hit2.hitPoint), XMVectorGetY(hit2.hitPoint));
	float f = targetRb->mass * powf(targetRb->angularVelocity * M_PI / 180, 2) * (PointToPointDistance(hitpoint.x, hitpoint.y, targetCollider->gameObject->position.x, targetCollider->gameObject->position.y));
	glm::vec2 force = glm::normalize(thisCollider->gameObject->position - hitpoint) * f;
	float f2 = rb->mass * powf(rb->angularVelocity * M_PI / 180, 2) * (PointToPointDistance(hitpoint.x, hitpoint.y, thisCollider->gameObject->position.x, thisCollider->gameObject->position.y));
	glm::vec2 force2 = glm::normalize(targetCollider->gameObject->position - hitpoint) * f;
	//printf("force: %f, %f, %f ,%f\n", f, XMVectorGetX(force), XMVectorGetY(force), XMVectorGetZ(force));
	targetRb->AddForceAtPoint(rb->velocity - force, hitpoint);
	rb->AddForceAtPoint(targetRb->velocity - force, hitpoint);
}

void Physics::HandleCollisionForRigidbody(Rigidbody* rb, Rigidbody* targetRb, CircleCollider* thisCollider, CircleCollider* targetCollider, glm::vec2 hitpoint)
{
	glm::vec3 or1 = glm::vec3(thisCollider->GetOffset().x, thisCollider->GetOffset().y, 1);
	or1 = thisCollider->GetRotateMatrix() * or1;

	Ray ray;
	ray.point = thisCollider->gameObject->position + glm::vec2(or1.x, or1.y);
	ray.direction = ray.point - hitpoint;

	/*Ray ray2;
	ray2.point = hitpoint;
	ray2.direction = ray2.point - (targetCollider->GetCenter() + or1);*/


	HitInfo hit1;//hit2;
	bool t1 = RaycastCollider(ray, *thisCollider, hit1);
	//bool t2 = RaycastCollider(ray, *targetCollider, hit2);
	if (!t1) {
		hit1.hitPoint = hitpoint;
	}
	/*if (!t2) {
		hit2.hitPoint = hitpoint;
	}*/
	glm::vec2 delta = hit1.hitPoint - hitpoint;
	//float dis = sqrtf(XMVectorGetX(delta) * XMVectorGetX(delta) + XMVectorGetY(delta) * XMVectorGetY(delta));
	//if (dis > PointToPointDistance(XMVectorGetX(thisCollider->GetCenter()), XMVectorGetY(thisCollider->GetCenter()), XMVectorGetX(targetCollider->GetCenter()), XMVectorGetY(targetCollider->GetCenter()))) {
	//	//printf("%f\n", dis);
	//	return;
	//}
	//printf("delta: %f,%f\n", XMVectorGetX(hitpoint), XMVectorGetY(hitpoint));
	//printf("delta: %f,%f\n", XMVectorGetX(ray.point), XMVectorGetY(ray.point));
	if (!rb->isStatic && !rb->isLockPosition) {
		thisCollider->gameObject->position -= delta;
	}
	if (!targetRb->isStatic && !targetRb->isLockPosition) {
		targetCollider->gameObject->position += delta;
	}
	if (rb->isLockPosition && targetRb->isLockPosition) {
		thisCollider->gameObject->position -= delta;
		targetCollider->gameObject->position += delta;
	}
	if (rb->isStatic || targetRb->isStatic) {
		return;
	}
	//printf("hit1: %f,%f\n", XMVectorGetX(hit1.hitPoint), XMVectorGetY(hit1.hitPoint));
	//printf("hit2: %f,%f\n", XMVectorGetX(hit2.hitPoint), XMVectorGetY(hit2.hitPoint));
	float f = targetRb->mass * powf(targetRb->angularVelocity * M_PI / 180, 2) * (PointToPointDistance(hitpoint.x, hitpoint.y, targetCollider->gameObject->position.x, targetCollider->gameObject->position.y));
	glm::vec2 force = glm::normalize(thisCollider->gameObject->position - hitpoint) * f;
	float f2 = rb->mass * powf(rb->angularVelocity * M_PI / 180, 2) * (PointToPointDistance(hitpoint.x, hitpoint.y, thisCollider->gameObject->position.x, thisCollider->gameObject->position.y));
	glm::vec2 force2 = glm::normalize(targetCollider->gameObject->position - hitpoint) * f;
	//printf("force: %f, %f, %f ,%f\n", f, XMVectorGetX(force), XMVectorGetY(force), XMVectorGetZ(force));
	targetRb->AddForceAtPoint(rb->velocity - force, hitpoint);
	rb->AddForceAtPoint(targetRb->velocity - force, hitpoint);
}

