#pragma once
#include "BaseAttack.h"
#include "../../Manager/ComponentManager.h"
#include "../../Utils/Utils.h"

class GameObject;

class MeleeAttack : public BaseAttack
{
private:
	Direction dir_ = RIGHT;
	AEVec2 attackDir;

	GameObject* aniObj_ = nullptr;

	MeleeAttack(GameObject* owner);

public:
	void Update() override;

	void On() override { owner_->active_ = true; }
	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void LevelUp() override;

	void AttackObject() override;

	Direction GetDirection() const { return dir_; }

	// for StateSerializer
	static constexpr const char* TypeName = "MeleeAttack";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};