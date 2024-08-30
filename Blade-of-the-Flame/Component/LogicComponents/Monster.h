#pragma once
#include <chrono>
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"
#include "../../Event/EventEntity.h"

class RigidBody;

class Monster : public LogicComponent, public EventEntity
{
private:
	int hp_ = 20;
	float moveSpeed_ = 2.5f;

	std::chrono::system_clock::time_point timeStart_;

	Transform* transPlayer = nullptr;
	Transform* trans = nullptr;
	RigidBody* rb = nullptr;

	Monster(GameObject* owner);

public:
	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event) override;

	// for StateSerializer
	static constexpr const char* TypeName = "Monster";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};