#pragma once
#include "State.h"

class GameObject;

class GameOver : public State
{
private:
	GameObject* obj = nullptr;

public:
	void Init() override;
	void Update() override;
	void Exit() override;
};