#pragma once
#include "EngineComponent.h"
#include "../Manager/ComponentManager.h"

class Sprite;

class Button : public EngineComponent
{
public:
	enum Todo
	{
		GAME,
		HOW_TO,
	};

private:
	Todo todo_;

	AEVec2 pos_;
	AEVec2 scl_;

	Transform* trans_ = nullptr;
	Sprite* sp_ = nullptr;
	Text* txt_ = nullptr;

	Button(GameObject* owner);

public:
	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void SetTodo(const Todo& todo) { todo_ = todo; }
	void SetScale(const AEVec2& scl);
	void SetPosition(const AEVec2& pos);
	void SetTexture(const std::string& name);
	void SetText(const std::string& str);

	// for StateSerializer
	static constexpr const char* TypeName = "Button";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<EngineComponent>;
};