#pragma once
#include "../LogicComponent.h"

class BaseItem : public LogicComponent
{
protected:
	bool use_;

	BaseItem(GameObject* owner);

public:
	void RemoveFromManager() override;
};