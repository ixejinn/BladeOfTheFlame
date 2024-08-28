#include "Score.h"

#include <typeindex>
#include "../../Manager/EventManager.h"
#include "../../GameObject/GameObject.h"
#include "../../Event/Event.h"

Score::Score(GameObject* owner) : LogicComponent(owner) {}

void Score::Update()
{
	if (score_ >= winScore_)
	{
		BaseEvent* event{ new GameOverEvent() };
		EventManager::GetInstance().AddEvent(event);
	}
}

void Score::LoadFromJson(const json&)
{
}

json Score::SaveToJson()
{
	return json();
}

void Score::OnEvent(BaseEvent* event)
{
	std::type_index eventType = std::type_index(typeid(*event));
	ScoreEvent* scoreEvent = static_cast<ScoreEvent*>(event);
	bool team = scoreEvent->scoreTeam;
	if (teamLeft == team && eventType == std::type_index(typeid(ScoreEvent)))
		score_++;
	else if (eventType == std::type_index(typeid(GameOverEvent)))
		score_ = 0;
}

ComponentSerializer* Score::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Score>())
		std::cout << "Score::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Score>();
}
