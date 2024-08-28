#pragma once
#include "../Serializer/ComponentSerializer.h"

class GameObject;

class Component : public ComponentSerializer
{
protected:
	GameObject* owner_;

public:
	Component(GameObject* owner) : owner_(owner) {}
	virtual ~Component() = default;

	virtual void Update() = 0;
};