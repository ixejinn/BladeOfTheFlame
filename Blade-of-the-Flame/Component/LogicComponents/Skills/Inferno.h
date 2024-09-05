//#pragma once
//#pragma once
//#include "../BaseAttack.h"
//#include "AEEngine.h"
//#include "../../../Manager/ComponentManager.h"
//
//class Inferno : public BaseAttack
//{
//	enum State
//	{
//		df,
//		ready,
//		shoot
//	};
//	Inferno(GameObject* owner);
//	int cState;
//public:
//	void Update() override;
//
//	void On() override { owner_->active_ = true; }
//
//	void LevelUp() override {};
//	float GetDmgGrowRate() { return dmgGrowthRate_; }
//	void AttackObject() override;
//
//	void LoadFromJson(const json&) override {};
//	json SaveToJson() override {return json();}
//
//	static constexpr const char* TypeName = "Skill_Inferno";
//	static ComponentSerializer* CreateComponent(GameObject* owner);
//
//	friend class ComponentManager<LogicComponent>;
//};