#pragma once
#include "AEEngine.h"
#include "../LogicComponent.h"
#include "../../Manager/ComponentManager.h"

class PlayerController : public LogicComponent
{
public:
	enum Direction { LEFT, RIGHT, UP, DOWN };

private:
	bool onlyUpDown = false;

	uint8_t moveKeys_[4] = { AEVK_A, AEVK_D, AEVK_W, AEVK_S };
	uint8_t rotKeys_[2] = { 0x00, 0x00 };
	uint8_t stopKey_ = 0x00;

	float moveSpeed_ = 30.f;
	float rotSpeed_ =  0.5f;

	PlayerController(GameObject* owner);

public:
	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void SetOnlyUpDown(bool b) { onlyUpDown = b; }
	void SetMoveKeys(Direction dir, uint8_t key) { moveKeys_[dir] = key; }
	void SetRotKeys(Direction dir, uint8_t key) { rotKeys_[dir] = key; }
	void SetStopKey(uint8_t key) { stopKey_ = key; }
	void SetMoveSpeed(float speed) { moveSpeed_ = speed; }
	void SetRotSpeed(float speed) { rotSpeed_ = speed; }

	void MultiplyMoveSpeed(float scale) { moveSpeed_ *= scale; }

	// for StateSerializer
	static constexpr const char* TypeName = "PlayerController";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};