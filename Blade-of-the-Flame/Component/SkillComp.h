#pragma once
#include "LogicComponent.h"
#include "../Manager/ComponentManager.h"
#include <map>

enum SkillType
{
	Default,
	Scorching,
	Flame,
	Haste,
	Fireball,
	Eating_Oxyzen,
	Meteor,
	Inferno
};

class SkillComp : public LogicComponent
{
	std::map<int, void(*)()> allSkill;
	bool Qactive = false;
	bool Eactive = false;
	bool Ractive = false;
	bool fire = false;

	void KeyCheck();
	void SetSkillType();

	//Skills
	void Scorching_Update();
	void Flame_Update();
	void Haste_Update();
	void Fireball_Update();
	void Eating_Oxyzen_Update();
	void Meteor_Update();
	void Inferno_Update();

	SkillComp(GameObject* owner);
	~SkillComp();
public:
	void Update() override;
	void RemoveFromManager() override;
	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	int type = Default;

	static constexpr const char* TypeName = "Skill";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};