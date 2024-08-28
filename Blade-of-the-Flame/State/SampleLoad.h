#pragma once
#include "State.h"

class SampleLoad : public State
{
private:

public:
	void Init() override;
	void Update() override;
	void Exit() override;
};