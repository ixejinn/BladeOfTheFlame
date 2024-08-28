#pragma once
#include "Component.h"

class AudioComponent : public Component
{
public:
	AudioComponent(GameObject* owner) : Component(owner) {}
	virtual ~AudioComponent() = default;
};