#pragma once
#include "Component.h"

class LogicComponent : public Component
{
public:
	LogicComponent(GameObject* owner) : Component(owner) {}
	virtual ~LogicComponent() = default;
};