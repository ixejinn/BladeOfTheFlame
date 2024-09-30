#pragma once
#include "BaseMonster.h"

#include "../../../Manager/ComponentManager.h"

class InstakillMonster : public BaseMonster
{
private:
	void SetAnimation() override;

	InstakillMonster(GameObject* owner);

public:

	friend class ComponentManager<LogicComponent>;
};