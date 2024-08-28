#pragma once
#include <string>
#include "LogicComponent.h"
#include "../Event/EventEntity.h"
#include "../Manager/ComponentManager.h"

class Score : public LogicComponent, public EventEntity
{
private:
	int score_ = 0;
	int winScore_ = 0;

	bool teamLeft = 0;

	Score(GameObject* owner);
	
public:
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event) override;

	int GetScore() { return score_; }

	void SetWinScore(const int& score) { winScore_ = score; }
	// @param b	0: Left(initial), 1: Right
	void SetTeam(bool b) { teamLeft = b; }

	void Reset() { score_ = 0; }

	// for StateSerializer
	static constexpr const char* TypeName = "Score";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};