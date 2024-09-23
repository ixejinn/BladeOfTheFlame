#pragma once
#include "State.h"

class GameObject;
class AnimationComp;

class OpeningLogos : public State
{
private:
	GameObject* digiLogo = nullptr;
	GameObject* teamLogo = nullptr;

	AnimationComp* digiAni = nullptr;
	AnimationComp* teamAni = nullptr;

public:
	void Init() override;
	void Update() override;
	void Exit() override;
};