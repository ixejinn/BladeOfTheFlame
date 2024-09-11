#include "MeleeAttack.h"

#include "AEVec2.h"
#include "../../Event/Event.h"
#include "../../Manager/EventManager.h"

MeleeAttack::MeleeAttack(GameObject* owner) : BaseAttack(owner)
{
	check = 0;
	dmg_ = 2;
	range_ = 100.f;
	cooldown_ = 0.5;
	dmgGrowthRate_ = 50.f;

	/* SET COMPONENTS */
	owner_->AddComponent<BoxCollider>();
	owner_->AddComponent<Sprite>();

	owner_->GetComponent<Transform>()->SetScale({ range_, range_ });
	BoxCollider* col = owner_->GetComponent<BoxCollider>();
	col->SetType(Collider::OBB_TYPE);
	col->SetLayer(Collider::P_ATTACK);
	owner_->GetComponent<Sprite>()->SetColor({ 100, 200, 100 });
}

void MeleeAttack::Update()
{
	if (check != 0)
	{
		check = 0;
		owner_->active_ = false;
	}
}

void MeleeAttack::LoadFromJson(const json&)
{
}

json MeleeAttack::SaveToJson()
{
	return json();
}

void MeleeAttack::LevelUp()
{
	dmg_ += int(dmg_ * dmgGrowthRate_ / 100);
}

void MeleeAttack::AttackObject()
{
	owner_->active_ = true;

	AEInputInit();
	s32 x, y;
	AEInputGetCursorPosition(&x, &y);
	AEVec2 attackDir{ x - windowWidth / 2.f, windowHeight / 2.f - y }, unitDir;
	AEVec2Normalize(&unitDir, &attackDir);

	attackDir = unitDir * range_;

	AEVec2 playerPos = player_->GetComponent<Transform>()->GetPosition();

	Transform* trans = owner_->GetComponent<Transform>();
	trans->SetPosition(playerPos + attackDir / 2.f);
	trans->SetScale({ range_, range_ });
	trans->SetRotation(unitDir);
	check++;
}

ComponentSerializer* MeleeAttack::CreateComponent(GameObject* owner)
{
	return nullptr;
}
//#include "MeleeAttack.h"
//
//#include "AEVec2.h"
//#include "../../Event/Event.h"
//#include "../../Manager/EventManager.h"
//#include "../../Manager/SkillManager.h"
//
//MeleeAttack::MeleeAttack(GameObject* owner) : BaseAttack(owner)
//{
//	state = set;
//	dmg_ = 5;
//	range_ = 100.f;
//	cooldown_ = 0.5;
//	dmgGrowthRate_ = 3.f;
//	owner->active_ = false;
//	/* SET COMPONENTS */
//	owner_->AddComponent<BoxCollider>();
//	owner_->AddComponent<Sprite>();
//
//	owner_->GetComponent<Transform>()->SetScale({ range_, range_ });
//	BoxCollider* col = owner_->GetComponent<BoxCollider>();
//	col->SetType(Collider::OBB_TYPE);
//	col->SetLayer(Collider::P_ATTACK);
//	owner_->GetComponent<Sprite>()->SetColor({ 100, 200, 100 });
//}
//
//void MeleeAttack::Update()
//{
//	if (!AEInputCheckCurr(AEVK_LBUTTON) && state == set)
//		state = go;
//	if (state == go)
//	{
//		AttackObject();
//		SkillManager::GetInstance().CooldownCountMelee = 0;
//		player_->GetComponent<Player>()->curAttack_ = nullptr;
//		SkillManager::GetInstance().resetKeys();
//		state = set;
//		owner_->active_ = false;
//	}
//}
//
//void MeleeAttack::LoadFromJson(const json&)
//{
//}
//
//json MeleeAttack::SaveToJson()
//{
//	return json();
//}
//
//void MeleeAttack::LevelUp()
//{
//	dmg_ += int(dmg_ * dmgGrowthRate_ / 100);
//}
//namespace
//{
//	AEVec2 convert(AEVec2 a)
//	{
//		AEVec2 worldPos;
//		worldPos.x = a.x - windowWidth / 2;
//		worldPos.y = -a.y + windowHeight / 2;
//		AEVec2 pos;
//		AEGfxGetCamPosition(&pos.x, &pos.y);
//		AEVec2 result;
//		result.x = worldPos.x + pos.x;
//		result.y = worldPos.y + pos.y;
//		return result;
//	}
//}
//void MeleeAttack::AttackObject()
//{
//	AEInputInit();
//	s32 x, y;
//	AEInputGetCursorPosition(&x, &y);
//	AEVec2 mousePosF({ static_cast<float>(x), static_cast<float>(y) });
//	AEVec2 attackDir{ convert(mousePosF)}, unitDir;
//	AEVec2Normalize(&unitDir, &attackDir);
//
//	attackDir = unitDir * range_;
//
//	// collider 설정하고
//	AEVec2 playerPos = player_->GetComponent<Transform>()->GetPosition();
//
//	Transform* trans = owner_->GetComponent<Transform>();
//	trans->SetPosition(playerPos + attackDir / 2.f);
//	trans->SetScale({ range_, range_ });
//	trans->SetRotation(unitDir);
//}
//
//ComponentSerializer* MeleeAttack::CreateComponent(GameObject* owner)
//{
//	return nullptr;
//}