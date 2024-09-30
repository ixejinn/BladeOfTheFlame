#pragma once
#include "AEEngine.h"
#include <vector>
#include <chrono>
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"
#include "../../Event/EventEntity.h"

class Boss1 : public LogicComponent, public EventEntity
{
private:
	enum E_bossState
	{
		_baseChase,
		_fastChase,
		_rangeAttack,
		_barrage,
	};

	E_bossState current_state;

	int hp_ = 0;
	int maxHp_ = 0;
	float moveSpeed_ = 0.f;
	float chaseSpeed_ = 0.f;
	float baseDmg_ = 0.f;
	float skillDmg_ = 0.f;
	float range_ = 0.f;

	double nomalphaseTime_ = 0.f;
	double DelayTime_ = 0.f;
	double shootTime_ = AEFrameRateControllerGetFrameTime();

	int phase1Count_ = 0;
	int phase2Count_ = 0;
	int shootCount_ = 0;

	float phase1_cool = 0;
	float phase2_cool = 0;
	float phase3_cool = 0;

	bool baseChase = false;

	bool phase1On = false;
	bool phase2On = false;
	bool phase3On = false;

	bool needShoot;
	bool isAction;

	double cooldown_ = 1.0;
	std::chrono::system_clock::time_point timeStart_;

	GameObject* player;

	std::vector<GameObject*> bullet;

	Boss1(GameObject* owner);

public:
	void Update() override;

	void RemoveFromManager() override;

	void OnEvent(BaseEvent* event) override;
	void OnCollision(CollisionEvent* event) override;

	const int& GetHp() const { return hp_; }
	const int& GetMaxHp() const { return maxHp_; }

	GameObject* CreateBulletObj();

	void BossState();
	

	void BaseChase();

	void Phase1();
	void Phase2();
	void Phase3();
	void Phase4();

	float Dot(const AEVec2& vec1, const AEVec2& vec2);

	bool Flip(AEVec2 flip);

	AEVec2 scale = { 0, 0 };

	void ReserveDmg(int dmg);

	void LoadFromJson(const json&);
	json SaveToJson();

	// for StateSerializer
	static constexpr const char* TypeName = "Boss1";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};