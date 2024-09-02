#pragma once
#include "AEVec2.h"
#include "EngineComponent.h"
#include "../Manager/ComponentManager.h"

class RigidBody : public EngineComponent
{
private:
	AEVec2 velocity_ = { 30.f,40.f };
	//AEVec2 velocity_;
	AEVec2 preVelocity_;
	AEVec2 maxVelocity_;

	bool useAcceleration_ = true;
	AEVec2 acceleration_;

	float dragCoefficient_ = 5.f;

	RigidBody(GameObject* owner);

	bool CheckEpsilon(float val, float EP = EPSILON);

public:
	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	const AEVec2& GetVelocity() { return velocity_; }

	void SetUseAcceleration(bool b) { useAcceleration_ = b; }
	void SetDragCoefficient(float x) { dragCoefficient_ = x; }
	void SetVelocity(AEVec2 setvleocity) { velocity_ = setvleocity; }

	void AddVelocity(const AEVec2& other);
	void AddVelocity(float x, float y);

	void ClearVelocity();

	// for StateSerializer
	static constexpr const char* TypeName = "RigidBody";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<EngineComponent>;
};