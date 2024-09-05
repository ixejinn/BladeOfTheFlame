#pragma once
#include "State.h"

class GameObject;

class MainMenu : public State
{
private:

public:
	void Init() override;
	void Update() override;
	void Exit() override;

	void InitBackground();
};