#pragma once
#include "AEEngine.h"
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"

class BulletComp : public LogicComponent
{
	
	float bulletDmg_ = 0.f;
	float bulletSpeed_ = 0.f;
	
	AEVec2 pos_;
	AEVec2 scale_;

	AEVec2 unitDir;

	GameObject* player;
	GameObject* boss;



	BulletComp(GameObject* ower);
	
public:
	float time = 0;

	bool phase2On = false;
	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void SetBulletSPeed(float bulletSpeed) { bulletSpeed_ = bulletSpeed; }
	void SetBulletDmage(float bulletDamge) { bulletDmg_   = bulletDamge; }

	void FireBullet();
	void testBullet();
	
	// for StateSerializer
	static constexpr const char* TypeName = "BulletComp";
	static ComponentSerializer* CreateComponent(GameObject* owner);

public:
	friend class ComponentManager<LogicComponent>;
};