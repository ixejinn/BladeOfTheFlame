#pragma once
#include "../BaseAttack.h"
#include "AEEngine.h"
#include "../../../Manager/ComponentManager.h"

class Flame : public BaseAttack
{
	enum State
	{
		df,
		ready,
		shoot
	};
	Flame(GameObject* owner);
	int cState;
	AEVec2 convertPos;
	AEVec2 unitDir;
	static int count;
	GameObject* fl;
public:
	void Update() override;

	void On() override { owner_->active_ = true; }
	AEVec2 GetUnitDir() const { return unitDir; }
	void LevelUp() override {};
	float GetDmgGrowRate() { return dmgGrowthRate_; }
	void AttackObject() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static constexpr const char* TypeName = "Skill_Flame";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};