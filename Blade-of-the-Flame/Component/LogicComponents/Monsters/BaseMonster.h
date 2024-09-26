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
		HURT,
		DIE
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

	Transform* trans_ = nullptr;
	RigidBody* rb_ = nullptr;
	AnimationComp* ani_ = nullptr;
	Sprite* sp_ = nullptr;

	Transform* playerTrans_ = nullptr;

	virtual void SetAnimation() = 0;

	// -1: despawned, 0: alive, 1: dead
	int CheckDeadState(const AEVec2& pos, const f32& squareDist);

	void MoveToPlayer(AEVec2& moveDir);

	BaseMonster(GameObject* owner);

public:
	void Update() override;

	void RemoveFromManager() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event) override;
	void OnCollision(CollisionEvent* event) override;

	const int GetDmg() const { return dmg_; }

	// for StateSerializer
	//static constexpr const char* TypeName = "Monster";
	//static ComponentSerializer* CreateComponent(GameObject* owner);
};