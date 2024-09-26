#pragma once
#include <chrono>
#include "../../LogicComponent.h"
#include "../../../Event/EventEntity.h"
#include "../../../Utils/Utils.h"

class Transform;
class RigidBody;
class AnimationComp;
class Sprite;
struct BaseEvent;
struct CollisionEvent;

class BaseMonster : public LogicComponent, public EventEntity
{
protected:
	enum State
	{
		MOVE,
		HURT
	};

	State state_ = MOVE;

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

	virtual void SetAnimation() = 0;

	BaseMonster(GameObject* owner);

public:
	void RemoveFromManager() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event) override;
	void OnCollision(CollisionEvent* event) override;

	const int GetDmg() const { return dmg_; }

	void HitMonster(int dmg) { hp_ -= dmg; }

	// for StateSerializer
	//static constexpr const char* TypeName = "Monster";
	//static ComponentSerializer* CreateComponent(GameObject* owner);
};