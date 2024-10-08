#include "FillBar.h"

#include <string>
#include <typeindex>
#include "../Manager/GameObjectManager.h"
#include "../Manager/MonsterManager.h"
#include "../Manager/EventManager.h"
#include "../Event/Event.h"
#include "../Utils/Utils.h"
#include "../Utils/MathUtils.h"

namespace Manager
{
	extern GameObjectManager& objMgr;
	extern ComponentManager<GraphicsComponent>& compGfxMgr;
	extern EventManager& evntMgr;
}

FillBar::FillBar(GameObject* owner) : GraphicsComponent(owner), showType_(), relativePos_(), scale_()
{
	// Pointer player
	GameObject* player = Manager::objMgr.GetObjectA("player");
	player_ = player->GetComponent<Player>();
	playerTrans_ = player->GetComponent<Transform>();

	// Background
	background_ = Manager::objMgr.CreateObject();
	background_->AddComponent<Transform>();
	background_->AddComponent<Sprite>();
	background_->AddComponent<RigidBody>();

	backTrans_ = background_->GetComponent<Transform>();

	background_->GetComponent<Sprite>()->SetColor(backColor_);

	// Fill
	fill_ = Manager::objMgr.CreateObject();
	fill_->AddComponent<Transform>();
	fill_->AddComponent<Sprite>();
	fill_->AddComponent<RigidBody>();

	fillTrans_ = fill_->GetComponent<Transform>();

	fill_->GetComponent<Sprite>()->SetAnchor(Sprite::LEFT_CENTER);

	// FillBar
	owner_->AddComponent<Text>();
	text_ = owner_->GetComponent<Text>();
	text_->SetFont("Assets/Roboto-Bold.ttf");
	text_->SetSize(1.f);

	boss_ = nullptr;
	Manager::evntMgr.RegisterEntity(std::type_index(typeid(SpawnBossEvent)), static_cast<EventEntity*>(this));
}

FillBar::~FillBar()
{
}

void FillBar::RemoveFromManager()
{
	Manager::compGfxMgr.GetInstance().DeleteComponent(static_cast<GraphicsComponent*>(this));
}

void FillBar::Update()
{
	// fill
	int value = 0;
	int maxValue = 1;
	static int maxMonsterCnt = 50;
	//static int maxMonsterCnt = 1;

	switch (showType_)
	{
	case MONSTER_CNT:
	{
		static int lvl = 0;

		value = MonsterManager::GetInstance().GetCapturedCount();
		text_->SetString(std::to_string(int(value)) + " / " + std::to_string(int(maxMonsterCnt)));
		text_->SetPosition({ -0.05f, 0.93f });

		Manager::compGfxMgr.ToBack(text_);

		if (value >= maxMonsterCnt)
		{
			lvl++;

			if (lvl < 4)
			{
				IncreaseBrightness* event = new IncreaseBrightness();
				event->from_ = owner_;
				event->level = lvl;
				Manager::evntMgr.AddEvent(static_cast<BaseEvent*>(event));

				maxMonsterCnt *= 2.8;
			}
			else
			{
				CompassActiveEvent* event = new CompassActiveEvent();
				event->from_ = owner_;
				Manager::evntMgr.AddEvent(static_cast<BaseEvent*>(event));
			}
			
		}
		maxValue = maxMonsterCnt;

		break;
	}

	case PLAYER_EXP:
		value = player_->GetExp();
		maxValue = player_->GetMaxExp();
		text_->SetString("LEVEL " + std::to_string(player_->GetLevel()) + "     " + std::to_string(int(value)) + " / " + std::to_string(int(maxValue)));
		text_->SetPosition({ -0.1f, -0.96f });
		Manager::compGfxMgr.ToBack(text_);
		break;

	case PLAYER_HP:
		value = player_->GetHp();
		if (value <= 0)
			value = 0;
		maxValue = player_->GetMaxHp();
		break;

	case BOSS_HP:
		value = boss_->GetHp();
		maxValue = boss_->GetMaxHp();
		break;

	case SKILL:
		value = player_->SkillGage;
		maxValue = player_->maxSkillGage;
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
	else if (showType_ != PLAYER_HP && showType_ != SKILL)
	{
		owner_->active_ = false;
		background_->active_ = false;
		fill_->active_ = false;
	}
}

void FillBar::OnCollision(CollisionEvent*)
{
}

void FillBar::UpdatePositionBasedOnPlayer()
{
	AEVec2 playerPos = playerTrans_->GetPosition();

	AEVec2 relativePos = relativePos_;
	backTrans_->SetPosition(playerPos + relativePos_);

	relativePos.x -= backTrans_->GetScale().x / 2;
	fillTrans_->SetPosition(playerPos + relativePos);
}

void FillBar::SetShowType(ShowType type)
{
	showType_ = type;

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
		relativePos_ = { 0, 40 };
		scale_ = { 51, 3 };
		fillColor_ = { 255, 0, 0 };
		break;

	case BOSS_HP:
		relativePos_ = { 0, windowHeight / 2 - 25 };
		scale_ = { windowWidth / 3, 30 };
		fillColor_ = { 255, 0, 0 };
		break;

	case SKILL:
		relativePos_ = { 0, 35 };
		scale_ = { 51, 3 };
		fillColor_ = { 255, 255, 0 };
		break;
	}
	backTrans_->SetScale(scale_);

	fill_->GetComponent<Sprite>()->SetColor(fillColor_);

	Manager::compGfxMgr.ToBack(fill_->GetComponent<Sprite>());
}

void FillBar::SetFillColor(Color color)
{
	fillColor_ = color;
}

void FillBar::SetBoss(Boss1* boss)
{
	boss_ = boss;

	SetShowType(BOSS_HP);

	//background_->active_ = false;
	//fill_->active_ = false;
	//owner_->active_ = false;
}

ComponentSerializer* FillBar::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<FillBar>())
		std::cout << "FillBar::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<FillBar>();
}
