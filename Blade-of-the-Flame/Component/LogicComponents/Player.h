#pragma once
#include <chrono>
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"
#include "../../Event/EventEntity.h"

class Text;
class BaseAttack;
class Audio;
class Transform;
class AnimationComp;

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
	float attractionRadius_ = 80.f;

	// Level up을 위해 필요한 경험치 증가율 (%)
	float expRequirement_ = 80.f;
	float hpGrowthRate_ = 20.;

	BaseAttack* curAttack_ = nullptr;			// Current basic attack
	GameObject* meleeAttack_ = nullptr;		// Player's melee attack  (level ~2)
	//GameObject* rangedAttack_ = nullptr;	// Player's ranged attack (level 3~)

	std::chrono::system_clock::time_point timeStart_;

	Transform* trans_;
	Audio* audio_;
	AnimationComp* ani_;

	void SetAnimation();

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