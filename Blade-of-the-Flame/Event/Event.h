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

/* PONG */

struct ScoreEvent : public BaseEvent
{
	bool scoreTeam = 0;	// Left: 0, Right: 1
};