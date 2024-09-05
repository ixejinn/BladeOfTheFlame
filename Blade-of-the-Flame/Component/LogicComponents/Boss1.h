#pragma once
#include "BossComp.h"

class Boss1 : public BossComp
{
	Boss1(GameObject* owner);

public:
	void Update() override;

	void BossState() override;

	void BaseChase() override;

	void Phase1() override;

	void Phase2() override;

	void Phase3() override;

	void Phase4() override;

	float Dot(const AEVec2& vec1, const AEVec2& vec2);

	bool Flip(AEVec2 flip);

	AEVec2 scale = { 0, 0 };

	void LoadFromJson(const json&);
	json SaveToJson();

	friend class ComponentManager<LogicComponent>;
};