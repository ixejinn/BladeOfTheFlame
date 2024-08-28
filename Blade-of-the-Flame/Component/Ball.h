#pragma once
#include "AEVec2.h"
#include "LogicComponent.h"
#include "../Manager/ComponentManager.h"
#include "../Event/EventEntity.h"
#include "../Utils/Utils.h"
#include "../Utils/RandomEngine.h"

class Ball : public LogicComponent, public EventEntity
{
private:
	const float ballStartYPos_[4] = {
		0.f, 50.f, 150.f, 250.f
	};
	std::uniform_int_distribution<int> startYPosIdx_{ -3, 3 };
	std::uniform_int_distribution<int> startXDir_{ 0, 1 };
	std::normal_distribution<double> startYDir_{ 0.0, windowHeight / 2.0 - 100.0 };
	int startXSign_ = 0;

	float speed_ = 700.f;

	const float wallSpeedUp = 1.001f;
	const float racketSpeedUp = 1.1f;

	AEVec2 unitReflDir_;

	Ball(GameObject* owner);

public:
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event) override;

	void SetCollisionPoint(const AEVec2& point);

	void Restart();

	// for StateSerializer
	static constexpr const char* TypeName = "Ball";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	// for setting
	static constexpr AEVec2 limit{ windowWidth / 2.f + 50.f, windowHeight / 2.f + 50.f };

	friend class ComponentManager<LogicComponent>;
};