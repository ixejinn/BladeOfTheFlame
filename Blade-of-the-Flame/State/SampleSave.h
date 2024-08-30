#pragma once
#include "State.h"

class GameObject;

class SampleSave : public State
{
private:
	GameObject* monster[5];

public:
	void Init() override;
	void Update() override;
	void Exit() override;
};