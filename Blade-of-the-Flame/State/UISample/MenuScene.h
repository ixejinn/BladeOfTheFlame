#pragma once
#include "../State.h"

class GameObject;

class MenuScene : public State
{

private:

public:
	void Init()override;
	void Update()override;
	void Exit()override;
};