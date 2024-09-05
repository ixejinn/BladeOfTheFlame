#pragma once
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"
#include "../../Event/EventEntity.h"

class FlameAltar;

class Compass : public LogicComponent, public EventEntity
{
private:
	FlameAltar* destination_ = nullptr;

	Transform* trans_ = nullptr;
	Transform* playerTrans_ = nullptr;
	Transform* destTrans_ = nullptr;

	Compass(GameObject* owner);

public:
	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event) override;
	void OnCollision(CollisionEvent* event) override;

	void SetDestination(GameObject* obj);

	// for StateSerializer
	static constexpr const char* TypeName = "Compass";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};