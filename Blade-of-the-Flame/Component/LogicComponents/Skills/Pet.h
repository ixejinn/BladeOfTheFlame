#pragma once
#include "AEEngine.h"
#include "../../LogicComponent.h"
#include "../../Component/AnimationComp.h"
#include "../../Manager/ComponentManager.h"

class Pet : public BaseAttack, public EventEntity
{
	enum
	{
		ready,
		shoot
	};
	Pet(GameObject* owner);
	float summon;
	float lifetime;
	AEVec2 dir;
	bool fire;
	int cState;
	~Pet();
public:

	void Update() override;

	void On() override { owner_->active_ = true; }

	void LevelUp() override;
	float GetDmgGrowRate() { return dmgGrowthRate_; }
	void AttackObject() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	// for StateSerializer
	static constexpr const char* TypeName = "PetComp";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	void OnEvent(BaseEvent*) override;
	void OnCollision(CollisionEvent*) override;

public:
	friend class ComponentManager<LogicComponent>;
};