#pragma once
#include "AEEngine.h"
#include "../../LogicComponent.h"
#include "../../Component/AnimationComp.h"
#include "../../Manager/ComponentManager.h"

class Grab : public BaseAttack, public EventEntity
{
	enum
	{
		set,
		fire
	};
	Grab(GameObject* owner);
	float lifetime;
	int mode;
	float tempdmg;
	AEVec2 dir;
	~Grab();
public:
	AEVec2 GetPos() { return owner_->GetComponent<Transform>()->GetPosition(); }

	void Update() override;

	void On() override { owner_->active_ = true; }

	void LevelUp() override;

	void AttackObject() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	// for StateSerializer
	static constexpr const char* TypeName = "GrabComp";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	void OnEvent(BaseEvent*) override;
	void OnCollision(CollisionEvent*) override;

public:
	friend class ComponentManager<LogicComponent>;
};