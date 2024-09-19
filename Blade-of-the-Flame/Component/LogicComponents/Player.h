#pragma once
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"
#include "../../Event/EventEntity.h"
#include "../../Manager/ParticleSystem.h"

class Text;
class BaseAttack;
class Audio;
class Transform;
class AnimationComp;

class Player : public LogicComponent, public EventEntity
{
private:
	static int count;

	int level_;
	int hp_ = 100;
	int exp_ = 0;

	int maxLevel_ = 10;
	int maxHp_ = 100;
	int maxExp_ = 100;

	int SkillGage = 0;

	float moveSpeed_ = 5.f;
	float attractionRadius_ = 80.f;

	float expRequirement_ = 80.f;
	float hpGrowthRate_ = 20.;

	//Basic_Attack
	GameObject* melee_Attack = nullptr;
	GameObject* double_flame_Attack = nullptr;
	GameObject* penetrable_double_flame_Attack = nullptr;

	//Special_Attack
	GameObject* shield_Attack = nullptr;
	GameObject* incendiary_Attack = nullptr;
	GameObject* meteor_Attack = nullptr;
	GameObject* fire_bubble_Attack = nullptr;

	Transform* trans_;
	Audio* audio_;
	AnimationComp* ani_;

	void SetAnimation();

	Player(GameObject* owner);

public:
	//Timer for Skills
	double meleeCool = 0;
	double flameCool = 0;
	double doubleflameCool = 0;
	double pendoubleflameCool = 0;

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