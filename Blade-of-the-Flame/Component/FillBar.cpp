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
	GameObject* player = GameObjectManager::GetInstance().GetObjectA("player");
	player_ = player->GetComponent<Player>();
	playerTrans_ = player->GetComponent<Transform>();

	background_ = GameObjectManager::GetInstance().CreateObject();
	background_->AddComponent<Transform>();
	background_->AddComponent<Sprite>();
	background_->AddComponent<RigidBody>();
	background_->AddComponent<PlayerController>();

	background_->GetComponent<Sprite>()->SetColor(backColor_);

	PlayerController* pCtrl = background_->GetComponent<PlayerController>();
	pCtrl->SetDashKey(AEVK_SPACE);
	pCtrl->MultiplyMoveSpeed(player_->GetMoveSpeed());

	owner_->AddComponent<Transform>();
	owner_->AddComponent<Text>();

	text_ = owner_->GetComponent<Text>();
	text_->SetFont("Assets/Roboto-Bold.ttf");
	text_->SetSize(1.f);

	backTrans_ = background_->GetComponent<Transform>();

	boss_ = nullptr;

	// Set mesh (Fill Object Ãß°¡ÇØ¼­ Sprite anchor¸¦ ¹Ù²ãÁàµµ µÊ)
	AEGfxMeshStart();

	Transform* trans = owner_->GetComponent<Transform>();
	AEVec2 length = { trans->GetLocalScale().x, trans->GetLocalScale().y };

	AEGfxTriAdd(
		0.f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		length.x, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.f, length.y - 0.5f, 0xFFFFFFFF, 0.0f, 0.0f
	);
	AEGfxTriAdd(
		length.x, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		length.x, length.y - 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		0.f, length.y - 0.5f, 0xFFFFFFFF, 0.0f, 0.0f
	);

	mesh_ = AEGfxMeshEnd();
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
		maxValue = 10;
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

	// Set background color
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	// Set render mode
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// Set color to multiply
	AEGfxSetColorToMultiply(1, 1, 1, 1);

	// Set color to add
	AEGfxSetColorToAdd(fillColor_.red / 255.f, fillColor_.green / 255.f, fillColor_.blue / 255.f, 0);

	// Set blend mode
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	// Set transparency
	AEGfxSetTransparency(1);

	// Set texture
	AEGfxTextureSet(nullptr, 0, 0);

	// Set transform
	AEMtx33 tranMtx;
	AEVec2 position = backTrans_->GetPosition();
	position.x -= scale_.x / 2;
	position.y -= 5;
	AEMtx33Trans(&tranMtx, position.x, position.y);

	AEMtx33 rotMtx;
	AEMtx33Rot(&rotMtx, 0);

	AEMtx33 sclMtx;
	AEMtx33Scale(&sclMtx, scale_.x * rate, scale_.y);

	// Concatenate trnasform, rotation, scaling matrix
	AEMtx33 transf;
	AEMtx33Concat(&transf, &rotMtx, &sclMtx);
	AEMtx33Concat(&transf, &tranMtx, &transf);

	AEGfxSetTransform(transf.m);

	// Draw mesh
	AEGfxMeshDraw(mesh_, AE_GFX_MDM_TRIANGLES);
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
	owner_->active_ = true;
}

void FillBar::OnCollision(CollisionEvent*)
{
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

	case BOSS_HP:
		relativePos_ = { 0, windowHeight / 2 - 25 };
		scale_ = { windowWidth / 3, 30 };
		break;
	}
	backTrans_->SetScale(scale_);

	AEVec2 playerPos = playerTrans_->GetPosition();
	backTrans_->SetPosition(playerPos + relativePos_);

	//ComponentManager<GraphicsComponent>::GetInstance().SwapComponent(this, background_->GetComponent<Sprite>());
	ComponentManager<GraphicsComponent>::GetInstance().ToBack(this);
	
}

void FillBar::SetFillColor(Color color)
{
	fillColor_ = color;
}

void FillBar::SetBoss(Boss1* boss)
{
	boss_ = boss;
	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(NextStageEvent)), static_cast<EventEntity*>(this));

	SetShowType(BOSS_HP);
	owner_->active_ = false;
}

ComponentSerializer* FillBar::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<FillBar>())
		std::cout << "FillBar::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<FillBar>();
}
