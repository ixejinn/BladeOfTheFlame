#pragma once
#include "BaseMonster.h"

#include "../../../Manager/ComponentManager.h"

class NormalMonster : public BaseMonster
{
private:
	void SetAnimation() override;

	NormalMonster(GameObject* owner);

	void Dead() override;

public:

	static constexpr const char* TypeName = "NormalMonster";

	friend class ComponentManager<LogicComponent>;
};