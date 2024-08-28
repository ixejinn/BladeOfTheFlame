#pragma once
#include "AEVec2.h"
#include "LogicComponent.h"
#include "../Manager/ComponentManager.h"
#include "../Event/EventEntity.h"
#include "../Utils/Utils.h"

class Racket : public LogicComponent, public EventEntity
{
private:
	const float transReflCenter_ = 40.f;

	Racket(GameObject* owner);

public:
	void Update() override;

	void LoadFromJson(const json& data) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event) override;

	const float& GetTransReflCenter() { return transReflCenter_; }

	// for StateSerializer
	static constexpr const char* TypeName = "Racket";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	// for setting
	static constexpr AEVec2 size{ 30, 110 };
	static constexpr float positionLeft{ -windowWidth / 2.f + 100 };
	static constexpr float positionRight{ windowWidth / 2.f - 100 };

	friend class ComponentManager<LogicComponent>;
};