#pragma once
#include "AEEngine.h"
#include "../../LogicComponent.h"
#include "../../Component/AnimationComp.h"
#include "../../Manager/ComponentManager.h"

class boomerang : public BaseAttack, public EventEntity
{
	enum
	{
		set,
		fire
	};
	boomerang(GameObject* owner);
	float lifetime;
	int mode;
	float angle_;
	float rotationSpeed_;
	float orbitRadius_;
	~boomerang();
public:

	void Update() override;

	void On() override { owner_->active_ = true; }

	void LevelUp() override;

	void AttackObject() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	// for StateSerializer
	static constexpr const char* TypeName = "boomerangComp";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	void OnEvent(BaseEvent*) override;
	void OnCollision(CollisionEvent*) override;

public:
	friend class ComponentManager<LogicComponent>;
};