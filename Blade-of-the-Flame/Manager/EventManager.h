#pragma once
#include <map>
#include <typeindex>	// std::type_index
#include <list>
#include <queue>
#include "../Event/EventEntity.h"

class EventManager
{
private:
	std::map<std::type_index, std::list<EventEntity*>> eventHandlers_;

	std::queue<BaseEvent*> events_;

	EventManager() = default;
	~EventManager() = default;

	EventManager(const EventManager&) = delete;
	EventManager& operator =(const EventManager&) = delete;
	EventManager(EventManager&&) = delete;
	EventManager& operator =(EventManager&&) = delete;

public:
	static EventManager& GetInstance()
	{
		static EventManager instance;
		return instance;
	}

	void AddEvent(BaseEvent* type);

	void RegisterEntity(const std::type_index& type, EventEntity* entity);
	void UnRegisterEntity(const std::type_index& type, EventEntity* entity);

	void ProcessEvent();
};