#pragma once
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"
#include "../../Event/EventEntity.h"

class Player : public LogicComponent, public EventEntity
{
private:
	int level_ = 1;
	int hp_ = 100;
	int exp_ = 0;

	int maxLevel_ = 10;
	int maxHp_ = 100;
	int maxExp_ = 100;

	int moveSpeed_ = 5;

	int baseDmg_ = 10;
	int attackRange_ = 3;
	float attackCooldown_ = 1.75f;

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

	// for StateSerializer
	static constexpr const char* TypeName = "Player";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};