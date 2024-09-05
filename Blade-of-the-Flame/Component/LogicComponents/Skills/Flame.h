//#pragma once
//#include "../BaseAttack.h"
//#include "AEEngine.h"
//#include "../../../Manager/ComponentManager.h"
//
//class Flame : public BaseAttack
//{
//	enum State
//	{
//		df,
//		ready,
//		shoot
//	};
//	Flame(GameObject* owner);
//	int cState;
//	float lifetime;
//	AEVec2 convertPos;
//	AEVec2 unitDir;
//
//	std::vector<GameObject*> flame;
//public:
//	void Update() override;
//
//	GameObject* CreateFlameObj(float lifeT, float flameD, float flameS, AEVec2 sca ,AEVec2 dir);
//
//	void On() override { owner_->active_ = true; }
//
//	void LevelUp() override {};
//
//	void AttackObject() override {};
//
//	void LoadFromJson(const json&) override;
//	json SaveToJson() override;
//
//	static constexpr const char* TypeName = "Skill_Flame";
//	static ComponentSerializer* CreateComponent(GameObject* owner);
//
//	friend class ComponentManager<LogicComponent>;
//};