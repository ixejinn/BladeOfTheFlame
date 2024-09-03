#pragma once
#include "../Attack.h"
#include "AEEngine.h"
#include "../../../Manager/ComponentManager.h"
 
class Meteor : public Attack
{
	enum State
	{
		ready,
		shoot
	};
	Meteor(GameObject* owner);
	int cState = ready;
public:
	bool onoff = false;

	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static constexpr const char* TypeName = "Skill_Meteor";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};