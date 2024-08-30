#pragma once

#include "AEEngine.h"
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"

class BulletComp : public LogicComponent
{
	
	float bulletDmg = 0.f;
	float bulletSpeed = 0.f;
	
	AEVec2 pos_;
	AEVec2 scale_;

	AEVec2 unitDir;

	GameObject* player;
	GameObject* boss;

	BulletComp(GameObject* ower); 

public:
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static std::string GetType()
	{
		return "BulletComp";
	}
	
	void InitBullet();

	// for StateSerializer
	static constexpr const char* TypeName = "RigidBody";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};