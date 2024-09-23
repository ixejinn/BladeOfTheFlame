#pragma once
#include "AEEngine.h"
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"
enum cState
{
	set,
	go
};
class Particle : public LogicComponent
{
	float dtemp;
	float delay = 0;
	Particle(GameObject* owner);
public:
	void RemoveFromManager() override;
	AEVec2 initialPos;
	AEVec2 initialVelocity;
	AEVec2 initialScale;
	float particleLifetime = 1000;
	int state = set;
	float temp;

	void SetDelay(float d) { delay = d; }
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	// for StateSerializer
	static constexpr const char* TypeName = "ParticleComp";
	static ComponentSerializer* CreateComponent(GameObject* owner);

public:
	friend class ComponentManager<LogicComponent>;
};