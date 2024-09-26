#pragma once
#include "AEEngine.h"
#include "../../LogicComponent.h"
#include "../../Component/AnimationComp.h"
#include "../../Manager/ComponentManager.h"

class PB : public BaseAttack, public EventEntity
{
	enum
	{
		set,
		fire
	};
	PB(GameObject* owner);
	float lifetime;
	~PB();
	int mode;
	AEVec2 dir;
public:
	AEVec2 goalPos;

	void Update() override;

	void On() override { owner_->active_ = true; }

	void LevelUp() override;

	void AttackObject() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	// for StateSerializer
	static constexpr const char* TypeName = "PBComp";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	void OnEvent(BaseEvent*) override;
	void OnCollision(CollisionEvent*) override;

public:
	friend class ComponentManager<LogicComponent>;
};