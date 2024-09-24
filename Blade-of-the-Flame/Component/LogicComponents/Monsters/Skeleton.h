#pragma once
#include "BaseMonster.h"

#include "../../../Manager/ComponentManager.h"

class Skeleton : public BaseMonster
{
private:
	void SetAnimation() override;

	Skeleton(GameObject* owner);

public:
	void Update() override;

	friend class ComponentManager<LogicComponent>;
};