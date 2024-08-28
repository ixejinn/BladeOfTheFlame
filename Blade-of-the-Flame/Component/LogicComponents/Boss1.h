#pragma once
#include "BossComp.h"

class Boss1 : public BossComp
{
	Boss1(GameObject* owner);

public:
	void Update() override;

	void baseAttack() override;

	void Phase1() override;

	void Phase2() override;

	void Phase3() override;
};