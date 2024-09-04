#pragma once
#include "AEEngine.h"
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"
class Particle : public LogicComponent
{
	enum cState
	{
		set,
		go
	};
	enum
	{
		Default,
		levelup,
		bullet
	};
	int state = set;
	GameObject* followTo = nullptr;
	float delay = 0;
	Particle(GameObject* owner);
public:
	int mode = Default;
	void RemoveFromManager() override;
	float GetLifetime() { return particleLifetime; }

	AEVec2 initialVelocity;
	AEVec2 initialScale{ 10, 10 };
	float particleLifetime = 1000;
	
	void SetFollowing(GameObject* obj) { followTo = obj; }
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