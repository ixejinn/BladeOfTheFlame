#pragma once
#include "AEVec2.h"
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"
#include "../../Event/EventEntity.h"
#include "Attack.h"

//// TODO: 기본 공격, 

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

	// Level up을 위해 필요한 경험치 증가율 (%)
	float expRequirement_ = 3.3f;
	float hpGrowthRate_ = 2.f;

	Attack* curAttack_ = nullptr;		// Current basic attack
	GameObject* meleeAttack_ = nullptr;		// Player's melee attack  (level ~2)
	//GameObject* rangedAttack_ = nullptr;	// Player's ranged attack (level 3~)

	Player(GameObject* owner);

public:
	void RemoveFromManager() override;

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