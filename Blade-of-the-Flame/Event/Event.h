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
	Collider::ColliderType fromType_;
};

struct GameOverEvent : public BaseEvent
{
};

struct MonsterAttackPlayer : public BaseEvent
{
	int dmg = 0;
};