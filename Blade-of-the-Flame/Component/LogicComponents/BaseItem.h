#pragma once
#include <chrono>
#include "../LogicComponent.h"
#include "../../Event/EventEntity.h"

class Transform;

class BaseItem : public LogicComponent, public EventEntity
{
protected:
	bool use_ = false;
	bool firstUse_ = true;

	double activeTime = 0.0;
	std::chrono::system_clock::time_point timeStart_;

	Transform* trans_;
	Transform* playerTrans_;

	BaseItem(GameObject* owner);

public:
	void RemoveFromManager() override;

	bool GetUse() const { return use_; }
	void SetUse(bool b) { use_ = b; }
};