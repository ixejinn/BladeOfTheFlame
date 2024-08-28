#pragma once

class State
{
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;
};