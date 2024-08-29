#pragma once
#include "../GameObject/GameObject.h"

// BaseEvent
struct BaseEvent
{
	GameObject* from_ = nullptr;

	virtual ~BaseEvent() {}
};

struct CollisionEvent : public BaseEvent
{
	GameObject* to_ = nullptr;
};

struct GameOverEvent : public BaseEvent
{

};