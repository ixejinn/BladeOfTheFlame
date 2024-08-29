#pragma once
#include "AEVec2.h"
#include "../LogicComponent.h"

class Attack : public LogicComponent
{
protected:
	GameObject* player_ = nullptr;

	int dmg_ = 10;
	int range_ = 3;
	double cooldown_ = 1.75;

	float dmgGrowthRate_ = 3.f;

	Attack(GameObject* owner) : LogicComponent(owner) {}

public:
	void SetPlayer(GameObject* player) { player_ = player; }

	virtual void LevelUp() = 0;

	virtual void AttackObject(s32 x, s32 y) = 0;
};