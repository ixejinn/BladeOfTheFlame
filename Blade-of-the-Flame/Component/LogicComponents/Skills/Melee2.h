#pragma once
#include "../BaseAttack.h"
#include "../../Manager/ComponentManager.h"

class Melee2Attack : public BaseAttack, public EventEntity
{
private:
	Melee2Attack(GameObject* owner);
	~Melee2Attack();
	float lifetime;
	float tempdmg;
	float elapsed;
public:
	enum
	{
		set,
		fire
	};

	int mode;

	float Getlifetime() const { return lifetime; }

	void Update() override;

	void On() override { owner_->active_ = true; }
	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void LevelUp() override;

	void AttackObject() override;

	// for StateSerializer
	static constexpr const char* TypeName = "Melee2Attack";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	void OnEvent(BaseEvent*) override;
	void OnCollision(CollisionEvent*) override;
	
	friend class ComponentManager<LogicComponent>;
};