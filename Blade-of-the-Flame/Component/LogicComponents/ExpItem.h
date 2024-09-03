#pragma once
#include "BaseItem.h"
#include "../../Manager/ComponentManager.h"

class ExpItem : public BaseItem
{
private:
	int exp_ = 0;
	float attractionSpeed_ = 30.f;

	RigidBody* rb_;

	ExpItem(GameObject* owner);

public:
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event) override;
	void OnCollision(CollisionEvent* event) override;

	void SetExp(int exp) { exp_ = exp; }

	// for StateSerializer
	static constexpr const char* TypeName = "ExpItem";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};