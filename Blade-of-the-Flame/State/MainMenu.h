#pragma once
#include "State.h"

class Button;

class MainMenu : public State
{
private:
	Button* startBtn_ = nullptr;
	Button* exitBtn_ = nullptr;

public:
	void Init() override;
	void Update() override;
	void Exit() override;

	void InitBackground();
};