#pragma once
#include "AEEngine.h"
#include "../../LogicComponent.h"
#include "../../AnimationComp.h"
#include "../../../Manager/ComponentManager.h"

class Shield : public BaseAttack, public EventEntity
{
	enum
	{
		set,
		fire
	};
	Shield(GameObject* owner);
	float lifetime;
	int mode;
	~Shield();
public:

	void Update() override;

	void On() override { owner_->active_ = true; }

	void LevelUp() override;

	void AttackObject() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	bool ac = false;

	// for StateSerializer
	static constexpr const char* TypeName = "ShieldComp";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	void OnEvent(BaseEvent*) override;
	void OnCollision(CollisionEvent*) override;

public:
	friend class ComponentManager<LogicComponent>;
};