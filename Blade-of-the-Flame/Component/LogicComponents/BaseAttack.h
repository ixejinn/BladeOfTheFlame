#pragma once
#include "../LogicComponent.h"

class BaseAttack : public LogicComponent
{
protected:
	int dmg_ = 0;
	float dmgGrowthRate_ = 0.f;

	float range_ = 0.f;

	double cooldown_ = 0.0;
	
	GameObject* player_ = nullptr;

	BaseAttack(GameObject* owner);

public:
	void RemoveFromManager() override;

	const int GetDmg() const { return dmg_; }
	const double GetCooldown() const { return cooldown_; }

	void SetPlayer(GameObject* player) { player_ = player; }

	virtual void LevelUp() = 0;

	virtual void On() = 0;

	virtual void AttackObject() = 0;
};