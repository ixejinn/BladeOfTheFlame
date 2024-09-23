#pragma once
#include "BaseItem.h"
#include "../../Manager/ComponentManager.h"

class HealthItem : public BaseItem
{
private:
	float hp_ = 0.2f;

	Player* player_ = nullptr;

	HealthItem(GameObject* owner);

public:
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event);
	void OnCollision(CollisionEvent* event);

	// for StateSerializer
	static constexpr const char* TypeName = "HealthItem";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};