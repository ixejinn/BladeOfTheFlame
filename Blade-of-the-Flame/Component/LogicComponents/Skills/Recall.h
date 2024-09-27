#pragma once
#include "AEEngine.h"
#include "../../LogicComponent.h"
#include "../../AnimationComp.h"
#include "../../../Manager/ComponentManager.h"

#include <vector>

class Recall : public BaseAttack
{
	enum
	{
		df,
		set,
		fire
	};
	static AEVec2 pPos;
	int check;
	std::vector<std::pair<AEVec2, float>> info;
	int mode;
	float elapsed;
	Recall(GameObject* owner);
	~Recall();
public:
	AEVec2 playerPos;
	float playerlife;

	void Update() override;

	void On() override { mode = fire; }

	void LevelUp() override;

	void AttackObject() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	// for StateSerializer
	static constexpr const char* TypeName = "RecallComp";
	static ComponentSerializer* CreateComponent(GameObject* owner);

public:
	friend class ComponentManager<LogicComponent>;
};