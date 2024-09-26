#pragma once
#include "BaseMonster.h"

#include "../../../Manager/ComponentManager.h"

class NormalMonster : public BaseMonster
{
private:
	void SetAnimation() override;

	NormalMonster(GameObject* owner);

public:

	friend class ComponentManager<LogicComponent>;
};