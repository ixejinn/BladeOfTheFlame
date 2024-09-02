#pragma once
#include <chrono>
#include "AEVec2.h"
#include "../LogicComponent.h"

class BaseAttack : public LogicComponent
{
protected:
	GameObject* player_ = nullptr;

	int dmg_ = 0;
	float range_ = 0.f;

	double cooldown_ = 0.0;

	float dmgGrowthRate_ = 0.f;

	BaseAttack(GameObject* owner);

public:
	const int GetDmg() const { return dmg_; }
	const double GetCooldown() const { return cooldown_; }

	void SetPlayer(GameObject* player) { player_ = player; }

	virtual void LevelUp() = 0;

	virtual void AttackObject() = 0;
};