#pragma once

#include "AEEngine.h"
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"

class BossComp : public LogicComponent
{
protected:
	float hp_         = 0.f;
	float moveSpeed_  = 0.f;
	float chaseSpeed_ = 0.f;
	float baseDmg_    = 0.f;
	float skillDmg_   = 0.f;
	float range_      = 0.f;
	
	AEVec2 pos_;
	AEVec2 scale_;

	BossComp(GameObject* owner);

public:
	void Update() override;

	static std::string GetType()
	{
		return "BossComp";
	}

	virtual void baseAttack() = 0;
	
	virtual void Phase1() = 0;

	virtual void Phase2() = 0;

	virtual void Phase3() = 0;

};