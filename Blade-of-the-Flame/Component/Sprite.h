#pragma once
#include <string>
#include "AEEngine.h"
#include "GraphicsComponent.h"
#include "../Utils/Utils.h"
#include "../Manager/ComponentManager.h"

class TextureResource;

class Sprite : public GraphicsComponent
{
public:
	enum AnchorPoint
	{
		CENTER,
		LEFT_CENTER,
		LEFT_UP
	};

private:
	AnchorPoint anchor_ = CENTER;
	AEVec2 localPos_ = { 0.f, 0.f };

	Color color_;
	unsigned char alpha_ = 0;

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

	void SetAnchor(AnchorPoint anchor);
	void SetLocalPos(float x, float y);
	void SetColor(const Color& col);
	void SetAlpha(const unsigned char& alpha) { alpha_ = alpha; }
	void SetTexture(const std::string& name);
	void SetTexture(TextureResource* texture);

	// for StateSerializer
	static constexpr const char* TypeName = "Sprite";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<GraphicsComponent>;
};