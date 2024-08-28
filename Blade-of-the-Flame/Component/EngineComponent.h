#pragma once
#include "Component.h"

class EngineComponent : public Component
{
public:
	EngineComponent(GameObject* owner) : Component(owner) {}
	virtual ~EngineComponent() = default;
};