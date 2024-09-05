#pragma once
#include "BaseItem.h"
#include "../../Manager/ComponentManager.h"

class MagnetItem : public BaseItem
{
private:
	float preRadius_ = 0.f;
	float radiusIncrease_ = 500.f;

	CircleCollider* playerCircle_;

	MagnetItem(GameObject* owner);

public:
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event);
	void OnCollision(CollisionEvent* event);

	// for StateSerializer
	static constexpr const char* TypeName = "MagnetItem";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};