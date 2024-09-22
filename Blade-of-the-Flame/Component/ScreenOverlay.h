#pragma once
#include <string>
#include "LogicComponent.h"
#include "../Event/EventEntity.h"
#include "../Manager/ComponentManager.h"

class Transform;
class Sprite;

class ScreenOverlay : public LogicComponent, public EventEntity
{
private:
	std::string textureName[4];

	Sprite* sp_ = nullptr;
	Transform* trans_ = nullptr;

	Transform* playerTrans_ = nullptr;

	ScreenOverlay(GameObject* owner);

public:
	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event) override;
	void OnCollision(CollisionEvent* event) override;

	// for StateSerializer
	static constexpr const char* TypeName = "ScreenOverlay";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};