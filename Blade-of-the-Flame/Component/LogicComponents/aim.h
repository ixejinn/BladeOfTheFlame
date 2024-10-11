#pragma once
#include "AEEngine.h"
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"
#include <vector>
class aim : public LogicComponent
{
	aim(GameObject* owner);
	~aim();
	float spin;
public:

	void Update() override;

	void LoadFromJson(const json&) override {};
	json SaveToJson() override { return json(); }

	void RemoveFromManager() override;

	// for StateSerializer
	static constexpr const char* TypeName = "aim";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};