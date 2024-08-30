#pragma once

#include "AEEngine.h"
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"

class BossComp : public LogicComponent
{

protected:

	enum BossState
	{
		Normal,
		FastChase,
		RangeAttack,
		Barrage,
	};
	BossState current_state;

	float hp_          = 0.f;
	float moveSpeed_   = 0.f;
	float chaseSpeed_  = 0.f;
	float baseDmg_     = 0.f;
	float skillDmg_    = 0.f;
	float range_       = 0.f;
	float phaseTime_   = 0.f;
	
	AEVec2 pos_;
	AEVec2 scale_;
	
	GameObject* player;
	
	BossComp(GameObject* owner);

public:
	void Update() override;
	
	void RemoveFromManager() override;

	static std::string GetType()
	{
		return "BossComp";
	}

	virtual void BossState() = 0;

	virtual void BaseChase() = 0;
	
	virtual void Phase1() = 0;

	virtual void Phase2() = 0;

	virtual void Phase3() = 0;
};