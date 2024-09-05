//#pragma once
//
//#include "AEEngine.h"
//#include <vector>
//#include <chrono>
//#include "../LogicComponent.h"
//#include "../../Manager/ComponentManager.h"
//#include "../../Event/EventEntity.h"
//
//class BossComp : public LogicComponent, public EventEntity
//{
//
//protected:
//
//	enum E_bossState
//	{
//		_baseChase,
//		_fastChase,
//		_rangeAttack,
//		_barrage,
//	};
//	E_bossState current_state;
//
//	float hp_          = 0.f;
//	float maxHp_       = 0.f;
//	float moveSpeed_   = 0.f;
//	float chaseSpeed_  = 0.f;
//	float baseDmg_     = 0.f;
//	float skillDmg_    = 0.f;
//	float range_       = 0.f;
//
//	float nomalphaseTime_ = 0.f;
//	float DelayTime_ = 0.f;
//	float shootTime_ = AEFrameRateControllerGetFrameTime();
//
//	int phase1Count_ = 0;
//	int phase2Count_ = 0;
//	int shootCount_ = 0;
//
//	float phase1_cool = 0;
//	float phase2_cool = 0;
//	float phase3_cool = 0;
//
//	bool baseChase = false;
//
//	bool phase1On  = false;
//	bool phase2On  = false;
//	bool phase3On  = false;
//
//	bool needShoot;
//	bool isAction;
//
//	AEVec2 pos_;
//	AEVec2 scale_;
//
//	double cooldown_ = 1.0;
//	std::chrono::system_clock::time_point timeStart_;
//	
//	GameObject* player;
//	GameObject* boss;
//
//	std::vector<GameObject*> bullet;
//
//	BossComp(GameObject* owner);
//
//public:
//	GameObject* CreateBulletObj();
//
//	void RemoveFromManager() override;
//
//	const int& GetHp() { return hp_; }
//	const int& GetMaxHp() { return maxHp_; }
//
//	static std::string GetType()
//	{
//		return "BossComp";
//	}
//
//	virtual void BossState() = 0;
//
//	virtual void BaseChase() = 0;
//	
//	virtual void Phase1() = 0;
//
//	virtual void Phase2() = 0;
//
//	virtual void Phase3() = 0;
//
//	virtual void Phase4() = 0;
//	// for StateSerializer
//
//	static constexpr const char* TypeName = "BossComp";
//	static ComponentSerializer* CreateComponent(GameObject* owner);
//
//	friend class ComponentManager<LogicComponent>;
//};