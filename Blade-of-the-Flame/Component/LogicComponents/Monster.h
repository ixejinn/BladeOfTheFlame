#pragma once
#include <chrono>
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"
#include "../../Event/EventEntity.h"
#include "../../Utils/Utils.h"

class RigidBody;
class AnimationComp;
class Sprite;

class Monster : public LogicComponent, public EventEntity
{
private:
	int hp_ = 0;
	int maxHp_ = 0;

	int exp_ = 0;

	int dmg_ = 0;
	float moveSpeed_ = 0.f;

	float knockback_ = 0.f;

	double cooldown_ = 0.0;
	std::chrono::system_clock::time_point timeStart_;

	Direction dir_ = RIGHT;

	Transform* playerTrans_ = nullptr;
	Transform* trans_ = nullptr;
	RigidBody* rb_ = nullptr;
	AnimationComp* ani_ = nullptr;
	Sprite* sp_ = nullptr;

	void SetAnimation();

	Monster(GameObject* owner);

public:
	enum State
	{
		MOVE,
		HURT
	};

	State state_ = MOVE;

	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event) override;
	void OnCollision(CollisionEvent* event) override;

	const int GetDmg() const { return dmg_; }

	void ReserveDmg(int dmg);

	// for StateSerializer
	static constexpr const char* TypeName = "Monster";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};