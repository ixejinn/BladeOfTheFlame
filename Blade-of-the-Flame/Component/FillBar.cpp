#include "FillBar.h"

#include <string>
#include <typeindex>
#include "../Manager/GameObjectManager.h"
#include "../Manager/MonsterManager.h"
#include "../Manager/EventManager.h"
#include "../../Event/Event.h"
#include "../../Utils/Utils.h"
#include "../../Utils/MathUtils.h"

FillBar::FillBar(GameObject* owner) : GraphicsComponent(owner), showType_(), relativePos_(), scale_()
{
	// Pointer player
	GameObject* player = GameObjectManager::GetInstance().GetObjectA("player");
	player_ = player->GetComponent<Player>();
	playerTrans_ = player->GetComponent<Transform>();

	// Background
	background_ = GameObjectManager::GetInstance().CreateObject();
	background_->AddComponent<Transform>();
	background_->AddComponent<Sprite>();
	background_->AddComponent<RigidBody>();
	background_->AddComponent<PlayerController>();

	backTrans_ = background_->GetComponent<Transform>();

	background_->GetComponent<Sprite>()->SetColor(backColor_);

	PlayerController* pCtrl = background_->GetComponent<PlayerController>();
	pCtrl->SetDashKey(AEVK_SPACE);
	pCtrl->MultiplyMoveSpeed(player_->GetMoveSpeed());

	// Fill
	fill_ = GameObjectManager::GetInstance().CreateObject();
	fill_->AddComponent<Transform>();
	fill_->AddComponent<Sprite>();
	fill_->AddComponent<RigidBody>();
	fill_->AddComponent<PlayerController>();

	fillTrans_ = fill_->GetComponent<Transform>();

	fill_->GetComponent<Sprite>()->SetAnchor(Sprite::LEFT_CENTER);

	pCtrl = fill_->GetComponent<PlayerController>();
	pCtrl->SetDashKey(AEVK_SPACE);
	pCtrl->MultiplyMoveSpeed(player_->GetMoveSpeed());

	// FillBar
	owner_->AddComponent<Text>();
	text_ = owner_->GetComponent<Text>();
	text_->SetFont("Assets/Roboto-Bold.ttf");
	text_->SetSize(1.f);

	boss_ = nullptr;
	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(NextStageEvent)), static_cast<EventEntity*>(this));
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
	static bool compass = true;

	// fill
	int value = 0;
	int maxValue = 1;
	switch (showType_)
	{
	case MONSTER_CNT:
	{
		value = MonsterManager::GetInstance().GetCapturedCount();
		maxValue = 1;
		text_->SetString(std::to_string(int(value)) + " / " + std::to_string(int(maxValue)));
		text_->SetPosition({ -0.05f, 0.93f });

		ComponentManager<GraphicsComponent>::GetInstance().ToBack(text_);

		if (compass && value >= maxValue)
		{
			CompassActiveEvent* event = new CompassActiveEvent();
			event->from_ = owner_;
			EventManager::GetInstance().AddEvent(static_cast<BaseEvent*>(event));
			compass = false;
		}
		break;
	}

	case PLAYER_EXP:
		value = player_->GetExp();
		maxValue = player_->GetMaxExp();
		text_->SetString("LEVEL " + std::to_string(player_->GetLevel()) + "     " + std::to_string(int(value)) + " / " + std::to_string(int(maxValue)));
		text_->SetPosition({ -0.1f, -0.96f });
		ComponentManager<GraphicsComponent>::GetInstance().ToBack(text_);
		break;

	case PLAYER_HP:
		value = player_->GetHp();
		maxValue = player_->GetMaxHp();
		break;

	case BOSS_HP:
		value = boss_->GetHp();
		maxValue = boss_->GetMaxHp();
		break;
	}

	if (value > maxValue)
		value = maxValue;
	float rate = float(value) / maxValue;

	fillTrans_->SetScale({ scale_.x * rate, scale_.y });
}

void FillBar::LoadFromJson(const json&)
{
}

json FillBar::SaveToJson()
{
	return json();
}

void FillBar::OnEvent(BaseEvent*)
{
	if (showType_ == BOSS_HP)
	{
		owner_->active_ = true;
		background_->active_ = true;
		fill_->active_ = true;
	}
	else if (showType_ != PLAYER_HP)
	{
		owner_->active_ = false;
		background_->active_ = false;
		fill_->active_ = false;
	}
}

void FillBar::OnCollision(CollisionEvent*)
{
}

void FillBar::SetShowType(ShowType type)
{
	showType_ = type;

	AEVec2 limit{ windowWidth, windowHeight };
	limit = limit * 4.f;
	AEVec2 upperLimit = limit, lowerLimit = limit * -1.f;

	switch (type)
	{
	case MONSTER_CNT:
		relativePos_ = { 0, windowHeight / 2 - 25 };
		scale_ = { windowWidth / 3, 30 };
		fillColor_ = { 200, 200, 200 };
		break;

	case PLAYER_EXP:
		relativePos_ = { 0, -windowHeight / 2 + 25 };
		scale_ = { windowWidth / 3, 30 };
		fillColor_ = { 0, 255, 0 };
		break;

	case PLAYER_HP:
	{
		AEVec2 playerScale = GameObjectManager::GetInstance().GetObjectA("player")->GetComponent<Transform>()->GetScale();
		relativePos_ = { 0, playerScale.y / 2 + 5 };
		scale_ = { 51, 3 };
		fillColor_ = { 255, 0, 0 };
		break;
	}

	case BOSS_HP:
		relativePos_ = { 0, windowHeight / 2 - 25 };
		scale_ = { windowWidth / 3, 30 };
		fillColor_ = { 255, 0, 0 };
		break;
	}
	backTrans_->SetScale(scale_);

	AEVec2 playerPos = playerTrans_->GetPosition();
	backTrans_->SetPosition(playerPos + relativePos_);

	relativePos_.x -= backTrans_->GetScale().x / 2;
	fillTrans_->SetPosition(playerPos + relativePos_);

	fill_->GetComponent<Sprite>()->SetColor(fillColor_);

	upperLimit.y += relativePos_.y;
	lowerLimit.y += relativePos_.y;
	backTrans_->SetUpperLimit(upperLimit);
	backTrans_->SetLowerLimit(lowerLimit);

	upperLimit.x -= scale_.x / 2.f;
	lowerLimit.x -= scale_.x / 2.f;
	fillTrans_->SetUpperLimit(upperLimit);
	fillTrans_->SetLowerLimit(lowerLimit);

	ComponentManager<GraphicsComponent>::GetInstance().ToBack(fill_->GetComponent<Sprite>());
	
}

void FillBar::SetFillColor(Color color)
{
	fillColor_ = color;
}

void FillBar::SetBoss(Boss1* boss)
{
	boss_ = boss;

	SetShowType(BOSS_HP);

	background_->active_ = false;
	fill_->active_ = false;
	owner_->active_ = false;
}

ComponentSerializer* FillBar::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<FillBar>())
		std::cout << "FillBar::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<FillBar>();
}
