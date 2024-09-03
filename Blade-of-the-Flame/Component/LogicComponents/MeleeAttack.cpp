#include "MeleeAttack.h"

#include "../../Event/Event.h"
#include "../../Manager/EventManager.h"

MeleeAttack::MeleeAttack(GameObject* owner) : BaseAttack(owner)
{
	dmg_ = 5;
	range_ = 100.f;
	cooldown_ = 0.5;
	dmgGrowthRate_ = 3.f;

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
	AEVec2 attackDir{ x - windowWidth / 2, windowHeight / 2 - y }, unitDir;
	AEVec2Normalize(&unitDir, &attackDir);

	attackDir = unitDir * range_;

	// collider 설정하고
	AEVec2 playerPos = player_->GetComponent<Transform>()->GetPosition();

	Transform* trans = owner_->GetComponent<Transform>();
	trans->SetPosition(playerPos + attackDir / 2.f);
	trans->SetScale({ range_, range_ });
	trans->SetRotation(unitDir);
}

ComponentSerializer* MeleeAttack::CreateComponent(GameObject* owner)
{
	return nullptr;
}
