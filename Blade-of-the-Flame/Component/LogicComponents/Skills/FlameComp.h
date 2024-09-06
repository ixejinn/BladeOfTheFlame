#pragma once
#include "AEEngine.h"
#include "../../LogicComponent.h"
#include "../../AnimationComp.h"
#include "../../../Manager/ComponentManager.h"

class FlameComp : public BaseAttack, public EventEntity
{
	enum
	{
		set,
		go
	};
	FlameComp(GameObject* owner);
	float lifetime;
	GameObject* flameInf;
	int mode;
	AEVec2 dir;
public:

	void Update() override;

	void On() override { owner_->active_ = true; }

	void LevelUp() override;

	void AttackObject() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	// for StateSerializer
	static constexpr const char* TypeName = "FlameComp";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	void OnEvent(BaseEvent*) override;
	void OnCollision(CollisionEvent*) override;

public:
	friend class ComponentManager<LogicComponent>;
};