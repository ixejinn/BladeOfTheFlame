//#pragma once
//#include "AEEngine.h"
//#include "../../LogicComponent.h"
//#include "../../Component/AnimationComp.h"
//#include "../../Manager/ComponentManager.h"
//
//class FlameComp : public BaseAttack
//{
//	AEVec2 pos_;
//	AEVec2 unitDir;
//	AEVec2 dir;
//	FlameComp(GameObject* ower);
//public:
//	float lifetime, tempLifetime;
//	float FlameDmg_;
//	float FlameSpeed_;
//	AEVec2 scale_;
//
//	void RemoveFromManager() override;
//
//	void Update() override;
//
//	void LoadFromJson(const json&) override;
//	json SaveToJson() override;
//
//	void FireFlame();
//
//	// for StateSerializer
//	static constexpr const char* TypeName = "FlameComp";
//	static ComponentSerializer* CreateComponent(GameObject* owner);
//
//public:
//	friend class ComponentManager<LogicComponent>;
//};