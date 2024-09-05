#pragma once
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"
#include "../../Event/EventEntity.h"
#include "../../Manager/ParticleSystem.h"

class Text;
class BaseAttack;
class Audio;
class Transform;

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
	float expRequirement_ = 80.f;
	float hpGrowthRate_ = 20.;

	GameObject* meleeAttack_ = nullptr;		// Player's melee attack  (level ~2)
	GameObject* Skills_Meteor = nullptr;
	GameObject* Skills_Flame = nullptr;
	//GameObject* rangedAttack_ = nullptr;	// Player's ranged attack (level 3~)

	Transform* trans_;
	Audio* audio_;

	Player(GameObject* owner);

public:
	bool getCompass_ = false;
	bool findAltar_ = false;

	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event) override;
	void OnCollision(CollisionEvent*) override;
	
	BaseAttack* curAttack_ = nullptr;			// Current basic attack

	const int& GetLevel() const { return level_; }
	const int& GetHp() const { return hp_; }
	const int& GetExp() const { return exp_; }
	const int& GetMaxHp() const { return maxHp_; }
	const int& GetMaxExp() const { return maxExp_; }
	const float& GetMoveSpeed() const { return moveSpeed_; }

	void LevelUp();
	void AddHp(int hp);
	void AddExp(int exp);

	// for StateSerializer
	static constexpr const char* TypeName = "Player";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};