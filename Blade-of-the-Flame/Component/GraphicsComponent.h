#pragma once
#include "Component.h"

class GraphicsComponent : public Component
{
public:
	GraphicsComponent(GameObject* owner) : Component(owner) {}
	virtual ~GraphicsComponent() = default;
};