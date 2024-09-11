//#pragma once
//#include "BaseAttack.h"
//#include "../../Manager/ComponentManager.h"
//
//class MeleeAttack : public BaseAttack
//{
//	enum cState
//	{
//		set,
//		go
//	};
//
//	MeleeAttack(GameObject* owner);
//	int state;
//public:
//	void Update() override;
//
//	void On() override { owner_->active_ = true; }
//
//	void LoadFromJson(const json&) override;
//	json SaveToJson() override;
//
//	void LevelUp() override;
//
//	void AttackObject() override;
//
//	// for StateSerializer
//	static constexpr const char* TypeName = "MeleeAttack";
//	static ComponentSerializer* CreateComponent(GameObject* owner);
//
//	friend class ComponentManager<LogicComponent>;
//};
#pragma once
#include "BaseAttack.h"
#include "../../Manager/ComponentManager.h"

class MeleeAttack : public BaseAttack
{
private:
	int check;
	MeleeAttack(GameObject* owner);
public:
	void Update() override;

	void On() override {}
	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void LevelUp() override;

	void AttackObject() override;

	// for StateSerializer
	static constexpr const char* TypeName = "MeleeAttack";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};