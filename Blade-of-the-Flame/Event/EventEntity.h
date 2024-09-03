#pragma once

struct BaseEvent;
struct CollisionEvent;

class EventEntity
{
public:
	virtual void OnEvent(BaseEvent*) = 0;
	virtual void OnCollision(CollisionEvent*) = 0;
};