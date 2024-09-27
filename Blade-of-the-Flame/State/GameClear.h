#pragma once
#include "State.h"

class Button;

class GameClear : public State
{
private:
	Button* mainBtn_ = nullptr;
	Button* exitBtn_ = nullptr;

public:
	void Init() override;
	void Update() override;
	void Exit() override;
};