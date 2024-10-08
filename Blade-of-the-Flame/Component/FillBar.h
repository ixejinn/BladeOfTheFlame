#pragma once
#include "AEVec2.h"
#include "../Manager/ComponentManager.h"

class Transform;
class Player;
class Boss1;

/**
* SetShowType 호출 필수
*/
class FillBar : public GraphicsComponent, public EventEntity
{
public:
	enum ShowType
	{
		MONSTER_CNT,
		PLAYER_EXP,
		PLAYER_HP,
		BOSS_HP,
		SKILL
	};

private:
	ShowType showType_;	// Set 사용하여 필수 설정
	AEVec2 relativePos_;
	AEVec2 scale_;

	GameObject* background_ = nullptr;
	GameObject* fill_ = nullptr;

	Color backColor_{ 100, 100, 100 };
	Color fillColor_{ 255, 100, 100 };

	Text* text_ = nullptr;

	Transform* backTrans_ = nullptr;
	Transform* fillTrans_ = nullptr;

	int monsterCntLvl = 0;

	Player* player_ = nullptr;
	Transform* playerTrans_ = nullptr;

	Boss1* boss_ = nullptr;

	FillBar(GameObject* owner);
	~FillBar();

public:
	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void OnEvent(BaseEvent*) override;
	void OnCollision(CollisionEvent*) override;

	void UpdatePositionBasedOnPlayer();

	void SetShowType(ShowType type);
	void SetRelativePos(AEVec2 pos) { relativePos_ = pos; }
	void SetScale(AEVec2 scale) { scale_ = scale; }
	void SetFillColor(Color color);

	void SetBoss(Boss1* boss);

	// for StateSerializer
	static constexpr const char* TypeName = "FillBar";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<GraphicsComponent>;
};