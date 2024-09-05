#pragma once
#include <chrono>
#include <random>
#include "../LogicComponent.h"
#include "../../Event/EventEntity.h"
#include "../../Manager/ComponentManager.h"

class FlameAltar : public LogicComponent, public EventEntity
{
private:
	std::chrono::system_clock::time_point timeStart_;
	double spawnPeriod_ = 60.0;

	Transform* trans_ = nullptr;
	Transform* playerTrans_ = nullptr;

	std::uniform_int_distribution<int> spawnX_{ -windowWidth * 4, windowWidth * 4 };
	std::uniform_int_distribution<int> spawnY_{ -windowHeight * 4, windowHeight * 4 };

	FlameAltar(GameObject* owner);

public:
	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event) override;
	void OnCollision(CollisionEvent* event);

	// for StateSerializer
	static constexpr const char* TypeName = "FlameAltar";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};