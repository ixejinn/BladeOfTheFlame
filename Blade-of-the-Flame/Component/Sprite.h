#pragma once
#include <string>
#include "AEEngine.h"
#include "GraphicsComponent.h"
#include "../Utils/Utils.h"
#include "../Manager/ComponentManager.h"

class Sprite : public GraphicsComponent
{
private:
	Color color_;

	AEGfxTexture* texture_;
	std::string textureName_;

	AEGfxVertexList* mesh_;

	Sprite(GameObject* owner);
	~Sprite();

public:
	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void SetMesh();

	Color& GetColor() { return color_; }

	void SetColor(const Color& col);
	void SetTexture(const std::string& name);

	// for StateSerializer
	static constexpr const char* TypeName = "Sprite";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<GraphicsComponent>;
};