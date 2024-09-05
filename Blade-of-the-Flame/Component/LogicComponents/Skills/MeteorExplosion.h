#pragma once
#include "../BaseAttack.h"
#include "AEEngine.h"
#include ".././../Manager/ComponentManager.h"
enum
{
	set, 
	go
};
class MeteorExplosion : public BaseAttack
{
	MeteorExplosion(GameObject* owner);
	float lifetime;
	AEVec2 Ps;
	GameObject* meteorInf;
	int mode;
public:
	void Update() override;

	void On() override { owner_->active_ = true; }

	void LevelUp() override;

	void AttackObject() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static constexpr const char* TypeName = "MeteorExplosion";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};