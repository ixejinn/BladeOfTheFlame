#pragma once
#include <chrono>
#include "AEEngine.h"
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"
#include "../../Event/EventEntity.h"

class BulletComp : public LogicComponent, public EventEntity
{
	
	float bulletDmg_ = 0.f;
	float bulletSpeed_ = 0.f;

	double cooldown_ = 1.0;
	std::chrono::system_clock::time_point timeStart_;

	GameObject* player;
	GameObject* boss1;
	GameObject* boss2;

	bool check_ = true;


	BulletComp(GameObject* ower);
	
public:
	bool isCheck = false;
	float time = 0.f;

	AEVec2 unitDir;
	bool phase2On = false;
	bool returnBullet = false;
	void RemoveFromManager() override;

	void Update() override;

	void OnEvent(BaseEvent* event) override;
	void OnCollision(CollisionEvent* event) override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void SetBulletSPeed(float bulletSpeed) { bulletSpeed_ = bulletSpeed; }
	void SetBulletDmage(float bulletDamge) { bulletDmg_   = bulletDamge; }

	void FireBullet();
	void BarrageBullet(bool _bool);
	void DownBullet();
	void CurveBullet();

	// for StateSerializer
	static constexpr const char* TypeName = "BulletComp";
	static ComponentSerializer* CreateComponent(GameObject* owner);

public:
	friend class ComponentManager<LogicComponent>;
};