#pragma once
#include <chrono>
#include "AEVec2.h"
#include "../LogicComponent.h"

class Attack : public LogicComponent
{
protected:
	GameObject* player_ = nullptr;

	int dmg_ = 10;

	float range_ = 3.f;

	double cooldown_ = 1.75;

	float dmgGrowthRate_ = 3.f;

	std::chrono::system_clock::time_point timeStart_;

	Attack(GameObject* owner) : LogicComponent(owner) {}

public:
	double GetCooldown() { return cooldown_; }

	void SetPlayer(GameObject* player) { player_ = player; }

	virtual void LevelUp() = 0;

	virtual void AttackObject() = 0;
};