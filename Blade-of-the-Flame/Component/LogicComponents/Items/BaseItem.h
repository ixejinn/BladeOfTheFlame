#pragma once
#include <chrono>
#include "../../LogicComponent.h"
#include "../../../Event/EventEntity.h"
#include "../../../Manager/SpawnManager.h"

class Transform;
class Player;

class BaseItem : public LogicComponent, public EventEntity
{
protected:
	bool use_ = false;
	bool firstUse_ = true;

	double activeTime = 0.0;
	std::chrono::system_clock::time_point timeStart_;

	Transform* trans_ = nullptr;

	Player* player = nullptr;
	Transform* playerTrans_ = nullptr;

	bool DeactiveIfFar();

	BaseItem(GameObject* owner);

public:
	void RemoveFromManager() override;

	void OnCollision(CollisionEvent* event) override;

	bool GetUse() const { return use_; }
	void SetUse(bool b) { use_ = b; }
};