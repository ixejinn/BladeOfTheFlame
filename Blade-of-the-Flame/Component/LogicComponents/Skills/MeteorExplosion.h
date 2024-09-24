#pragma once
#include "../BaseAttack.h"
#include "AEEngine.h"
#include "../../../Manager/ComponentManager.h"
//**//
#include "../../../Event/EventEntity.h"
											//**//
class MeteorExplosion : public BaseAttack, public EventEntity
{
	enum cState
	{
		set,
		go
	};
	MeteorExplosion(GameObject* owner);
	float lifetime;
	AEVec2 Ps;
	int mode;
public:
	void Update() override;

	void On() override { owner_->active_ = true; }

	void LevelUp() override;

	void AttackObject() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	//**//
	void OnEvent(BaseEvent*) override;
	void OnCollision(CollisionEvent*) override;

	static constexpr const char* TypeName = "MeteorExplosion";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};