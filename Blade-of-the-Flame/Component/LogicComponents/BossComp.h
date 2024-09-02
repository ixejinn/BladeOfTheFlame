#pragma once

#include "AEEngine.h"
#include <vector>
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

	float nomalphaseTime_ = 0.f;
	float DelayTime_ = 0.f;
	float shootTime_ = AEFrameRateControllerGetFrameTime();

	int phase1Count_ = 0;
	int phase2Count_ = 0;
	int shootCount_ = 0;
	bool phaseOn = false;

	AEVec2 pos_;
	AEVec2 scale_;
	
	GameObject* player;
	GameObject* boss;

	std::vector<GameObject*> bullet;

	BossComp(GameObject* owner);

public:
	GameObject* CreateBulletObj();

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
	// for StateSerializer

	static constexpr const char* TypeName = "BossComp";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};