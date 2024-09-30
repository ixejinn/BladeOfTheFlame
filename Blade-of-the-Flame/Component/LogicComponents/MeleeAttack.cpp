#include "MeleeAttack.h"

#include "AEVec2.h"
#include "../../Event/Event.h"
#include "../../Manager/EventManager.h"

MeleeAttack::MeleeAttack(GameObject* owner) : BaseAttack(owner)
{
	dmg_ = 2;
	dmgGrowthRate_ = 50.f;

	range_ = 100.f;

	/* SET COMPONENTS */
	owner_->AddComponent<BoxCollider>();

	BoxCollider* col = owner_->GetComponent<BoxCollider>();
	col->SetType(Collider::OBB_TYPE);
	col->SetLayer(Collider::P_ATTACK);
}

void MeleeAttack::Update()
{
	AEInputInit();
	s32 x, y;
	AEInputGetCursorPosition(&x, &y);
	attackDir = { x - windowWidth / 2.f, windowHeight / 2.f - y };
	AEVec2 unitDir;
	AEVec2Normalize(&unitDir, &attackDir);

	attackDir = unitDir * range_;

	AEVec2 playerPos = player_->GetComponent<Transform>()->GetPosition();
	Transform* trans = owner_->GetComponent<Transform>();

	trans->SetPosition(playerPos + attackDir / 2);
	trans->SetRotation(unitDir);

	if (unitDir.x >= 0)
		dir_ = RIGHT;
	else
		dir_ = LEFT;

	owner_->active_ = false;
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
}

ComponentSerializer* MeleeAttack::CreateComponent(GameObject* owner)
{
	return nullptr;
}
