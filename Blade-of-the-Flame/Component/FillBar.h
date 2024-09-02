#pragma once
#include "AEEngine.h"
#include "../Manager/ComponentManager.h"

class Transform;
class Player;

class FillBar : public GraphicsComponent
{
private:
	AEGfxVertexList* backMesh_;

	Color backColor_{ 0, 0, 0 };
	Color fillColor_{ 200, 200, 200 };

	Transform* trans_ = nullptr;

	Transform* playerTrans_ = nullptr;
	Player* player_ = nullptr;

	FillBar(GameObject* owner);
	~FillBar();

public:
	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void SetFillColor(Color color) { fillColor_ = color; }

	// for StateSerializer
	static constexpr const char* TypeName = "FillBar";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<GraphicsComponent>;
};