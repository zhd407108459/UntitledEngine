#pragma once

class GameObject;

class GameComponent
{
	friend class GameObject;

private:
	bool isActive;


public:
	GameObject* gameObject;

	bool IsActive();
	void SetActive(bool flag);

	virtual void Start();

	virtual void Update(float deltaTime);
};

