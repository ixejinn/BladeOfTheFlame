#pragma once
#include "State.h"

class GameObject;

class GameClear : public State
{
private:
	GameObject* obj = nullptr;

public:
	void Init() override;
	void Update() override;
	void Exit() override;
};