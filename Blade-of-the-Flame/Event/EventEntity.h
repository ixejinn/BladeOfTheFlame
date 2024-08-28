#pragma once

struct BaseEvent;

class EventEntity
{
public:
	virtual void OnEvent(BaseEvent*) = 0;
};