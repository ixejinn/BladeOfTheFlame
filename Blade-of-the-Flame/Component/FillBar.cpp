#include "FillBar.h"
#include "../Manager/GameObjectManager.h"
#include "../Manager/MonsterManager.h"
#include "../../Utils/Utils.h"
#include "../../Utils/MathUtils.h"

FillBar::FillBar(GameObject* owner) : GraphicsComponent(owner), showType_(), relativePos_(), scale_()
{
	background_ = GameObjectManager::GetInstance().CreateObject();
	background_->AddComponent<Transform>();
	background_->AddComponent<Sprite>();
	background_->GetComponent<Sprite>()->SetColor(backColor_);

	fill_ = GameObjectManager::GetInstance().CreateObject();
	fill_->AddComponent<Transform>();
	fill_->AddComponent<Sprite>();

	owner_->AddComponent<Transform>();
	//owner_->AddComponent<Text>();

	//text_ = owner_->GetComponent<Text>();

	backTrans_ = background_->GetComponent<Transform>();
	fillTrans_ = fill_->GetComponent<Transform>();

	GameObject* player = GameObjectManager::GetInstance().GetObjectA("player");
	player_ = player->GetComponent<Player>();
	playerTrans_ = player->GetComponent<Transform>();
}

FillBar::~FillBar()
{
}

void FillBar::RemoveFromManager()
{
	ComponentManager<GraphicsComponent>::GetInstance().DeleteComponent(static_cast<GraphicsComponent*>(this));
}

void FillBar::Update()
{
	AEVec2 playerPos = playerTrans_->GetPosition();

	// background
	backTrans_->SetPosition(playerPos + relativePos_);

	// fill
	float value = 0.f;
	float maxValue = 0.f;
	switch (showType_)
	{
	case MONSTER_CNT:
		value = MonsterManager::GetInstance().GetCapturedCount();
		maxValue = 100;
		break;

	case PLAYER_EXP:
		value = player_->GetExp();
		maxValue = player_->GetMaxExp();
		break;

	case PLAYER_HP:
		value = player_->GetHp();
		maxValue = player_->GetMaxHp();
		break;
	}

	float startX = playerPos.x - scale_.x / 2;
	float rate = value / maxValue;

	float length = scale_.x * rate;
	float x = startX + length / 2.f;
	AEVec2 fillPos = playerPos + relativePos_;
	fillPos.x = x;

	fillTrans_->SetPosition(fillPos);
	fillTrans_->SetScale({ length, scale_.y });
}

void FillBar::LoadFromJson(const json&)
{
}

json FillBar::SaveToJson()
{
	return json();
}

void FillBar::SetShowType(ShowType type)
{
	showType_ = type;

	switch (type)
	{
	case MONSTER_CNT:
		relativePos_ = { 0, windowHeight / 2 - 25 };
		scale_ = { windowWidth / 3, 30 };
		break;

	case PLAYER_EXP:
		relativePos_ = { 0, -windowHeight / 2 + 25 };
		scale_ = { windowWidth / 3, 30 };
		break;

	case PLAYER_HP:
	{
		AEVec2 playerScale = GameObjectManager::GetInstance().GetObjectA("player")->GetComponent<Transform>()->GetScale();
		relativePos_ = { 0, playerScale.y / 2 + 5 };
		scale_ = { 51, 3 };
		break;
	}
	}
	backTrans_->SetScale(scale_);
}

void FillBar::SetFillColor(Color color)
{
	fill_->GetComponent<Sprite>()->SetColor(color);
}

ComponentSerializer* FillBar::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<FillBar>())
		std::cout << "FillBar::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<FillBar>();
}
