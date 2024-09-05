#pragma once
#include <chrono>
#include "AEVec2.h"
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"
#include "../../Event/EventEntity.h"
#include "../../Manager/ParticleSystem.h"
#include "BaseAttack.h"

class Text;

class Player : public LogicComponent, public EventEntity
{
private:
	int level_ = 1;
	int hp_ = 100;
	int exp_ = 0;

	int maxLevel_ = 10;
	int maxHp_ = 100;
	int maxExp_ = 1;

	float moveSpeed_ = 5.f;
	float attractionRadius_ = 80.f;

	// Level up을 위해 필요한 경험치 증가율 (%)
	float expRequirement_ = 3.3f;
	float hpGrowthRate_ = 2.f;

	GameObject* meleeAttack_ = nullptr;		// Player's melee attack  (level ~2)
	GameObject* Skills_Meteor = nullptr;
	GameObject* Skills_Flame = nullptr;
	//GameObject* rangedAttack_ = nullptr;	// Player's ranged attack (level 3~)


	Text* text_;
	Transform* trans_;

	Player(GameObject* owner);

public:
	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event) override;
	void OnCollision(CollisionEvent*) override;

	//// TODO: getter, setter
	const int GetLevel() const { return level_; }
	
	BaseAttack* curAttack_ = nullptr;			// Current basic attack
	void LevelUp();
	void AddHp(int hp);
	void AddExp(int exp);

	// for StateSerializer
	static constexpr const char* TypeName = "Player";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};