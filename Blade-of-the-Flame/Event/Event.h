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
	bool attackMonster = false;	// Event to attack monster
};

struct GameOverEvent : public BaseEvent
{

};