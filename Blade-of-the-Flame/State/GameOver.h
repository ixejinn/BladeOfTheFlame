#pragma once
#include "State.h"

class GameObject;

class GameOver : public State
{
private:
	GameObject* obj;

public:
	void Init() override;
	void Update() override;
	void Exit() override;
};