#pragma once
#include "BaseItem.h"
#include "../../Manager/ComponentManager.h"

class ExpItem : public BaseItem
{
private:
	float attractionSpeed_ = 15.f;

	Transform* trans_;
	Transform* playerTrans_;
	RigidBody* rb_;

	ExpItem(GameObject* owner);

public:
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event);
	void OnCollision(CollisionEvent* event);

	// for StateSerializer
	static constexpr const char* TypeName = "ExpItem";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};