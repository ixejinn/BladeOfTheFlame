#pragma once
#include "AEEngine.h"
#include "../BaseAttack.h"
#include "../../../Manager/ComponentManager.h"
#include "../../../Event/EventEntity.h"

class PenetrableDoubleFlameL : public BaseAttack, public EventEntity
{
	enum
	{
		set,
		fire
	};
	PenetrableDoubleFlameL(GameObject* owner);
	float lifetime;
	int mode;
	float tempdmg;
	AEVec2 dir;
	~PenetrableDoubleFlameL();
public:

	void Update() override;

	void On() override { owner_->active_ = true; }

	void LevelUp() override;

	void AttackObject() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	// for StateSerializer
	static constexpr const char* TypeName = "PenetrableDoubleFlameLComp";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	void OnEvent(BaseEvent*) override;
	void OnCollision(CollisionEvent*) override;

public:
	friend class ComponentManager<LogicComponent>;
};