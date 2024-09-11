//#pragma once
//#include "../BaseAttack.h"
//#include "AEEngine.h"
//#include "../../../Manager/ComponentManager.h"
// 
//class Meteor : public BaseAttack
//{
//	enum State
//	{
//		df,
//		ready,
//		shoot
//	};
//	Meteor(GameObject* owner);
//	int cState;
//	AEVec2 convertPos;
//	const AEVec2 startingOffset{ 5000 ,5000 };
//	float meteorLifetime;
//	GameObject* explosion;
//public:
//	void Update() override;
//
//	void On() override { owner_->active_ = true; }
//
//	void LevelUp() override;
//	float GetDmgGrowRate() { return dmgGrowthRate_; }
//	void AttackObject() override;
//
//	void LoadFromJson(const json&) override;
//	json SaveToJson() override;
//
//	static constexpr const char* TypeName = "Skill_Meteor";
//	static ComponentSerializer* CreateComponent(GameObject* owner);
//
//	friend class ComponentManager<LogicComponent>;
//};