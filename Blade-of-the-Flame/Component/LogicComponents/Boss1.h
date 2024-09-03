#pragma once
#include "BossComp.h"

class Boss1 : public BossComp
{
	Boss1(GameObject* owner);

	bool needShoot;
	bool isAction;

public:
	void Update() override;

	void BossState() override;

	void BaseChase() override;

	void Phase1() override;

	void Phase2() override;

	void Phase3() override;

	void Phase4() override;


	void LoadFromJson(const json&);
	json SaveToJson();

	friend class ComponentManager<LogicComponent>;
};