#include "EventManager.h"

#include "../Event/Event.h"

void EventManager::AddEvent(BaseEvent* type)
{
	events_.push(type);
}

void EventManager::RegisterEntity(const std::type_index& type, EventEntity* entity)
{
	eventHandlers_[type].push_back(entity);
}

void EventManager::UnRegisterEntity(const std::type_index& type, EventEntity* entity)
{
	auto& entities = eventHandlers_[type];

	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		if (*it == entity)
		{
			entities.erase(it);
			return;
		}
	}
}

void EventManager::ProcessEvent()
{
	while (!events_.empty())
	{
		BaseEvent* event = events_.front();
		auto& entities = eventHandlers_[std::type_index(typeid(*event))];

		for (auto it = entities.begin(); it != entities.end(); ++it)
			(*it)->OnEvent(event);

		delete event;
		events_.pop();
	}
}
