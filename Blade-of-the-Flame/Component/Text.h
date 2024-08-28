#pragma once

#include <string>
#include "AEEngine.h"
#include "GraphicsComponent.h"
#include "../Event/EventEntity.h"
#include "../Manager/ComponentManager.h"
#include "../Utils/Utils.h"

class Text : public GraphicsComponent, public EventEntity
{
private:
	std::string string_;

	s8 fontId_ = -1;
	std::string fontName_;

	AEVec2 position_{ 0.f, 0.f };
	float size_{ 10.f };
	Color color_{ 255, 255, 255 };

	Text(GameObject* owner);
	~Text();

public:
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent* event) override;

	void SetFont(const std::string& name);
	void SetString(const std::string& str) { string_ = str; }
	void SetPosition(const AEVec2& position) { position_ = position; }
	void SetSize(const float& size) { size_ = size; }
	void SetColor(const Color& col) { color_ = col; }

	// for StateSerializer
	static constexpr const char* TypeName = "Text";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<GraphicsComponent>;
};