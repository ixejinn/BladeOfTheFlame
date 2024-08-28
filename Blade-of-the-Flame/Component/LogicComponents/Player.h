#pragma once
#include "AEVec2.h"
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"
#include "../../Event/EventEntity.h"

//// TODO: 공격 유지 시간?

class Player : public LogicComponent, public EventEntity
{
private:
	int level_ = 1;
	int hp_ = 100;
	int exp_ = 0;

	int maxLevel_ = 10;
	int maxHp_ = 100;
	int maxExp_ = 100;

	float moveSpeed_ = 5.f;

	int baseDmg_ = 10;
	int attackRange_ = 3;
	double attackCooldown_ = 1.75;

	// Level up을 위해 필요한 경험치 증가율 (%)
	float expRequirement_ = 3.3f;

	float hpGrowthRate_ = 2.f;
	float baseDmgGrowthRate_ = 3.f;

	Player(GameObject* owner);

public:
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event) override;

	//// TODO: getter, setter

	void LevelUp();

	void BasicAttack(s32 x, s32 y);

	// for StateSerializer
	static constexpr const char* TypeName = "Player";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};