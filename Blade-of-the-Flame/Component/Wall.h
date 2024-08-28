#pragma once
#include "LogicComponent.h"
#include "Sprite.h"
#include "../Manager/ComponentManager.h"
#include "../Event/Event.h"
#include "../Utils/Utils.h"

class Wall : public LogicComponent
{
private:
	Wall(GameObject* owner);

public:
	void Update() override;

	void LoadFromJson(const json& data) override;
	json SaveToJson() override;

	// for StateSerializer
	static constexpr const char* typeName = "Wall";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	// for setting
	static constexpr AEVec2 size{ windowWidth, 30.f };
	static constexpr AEVec2 position{ 0.f, windowHeight / 2.f - size.y / 2.f };

	friend class ComponentManager<LogicComponent>;
};