#pragma once
#include "BaseMonster.h"

#include "../../../Manager/ComponentManager.h"

class InstakillMonster : public BaseMonster
{
private:
	void SetAnimation() override;

	void Dead() override;

	InstakillMonster(GameObject* owner);

public:

	static constexpr const char* TypeName = "InstakillMonster";

	friend class ComponentManager<LogicComponent>;
};