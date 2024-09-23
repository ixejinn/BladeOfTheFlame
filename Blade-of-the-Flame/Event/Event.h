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

struct CompassActiveEvent : public BaseEvent {};

struct LevelUpEvent : public BaseEvent
{
	int level;
};

struct IncreaseBrightness : public BaseEvent
{
	int level;
};

struct SpawnBossEvent : public BaseEvent {};

struct GameClearEvent : public BaseEvent {};
struct GameOverEvent : public BaseEvent {};