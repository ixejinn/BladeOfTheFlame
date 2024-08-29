#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(GameObject* owner) : Attack(owner)
{
	owner_->active_ = false;

	/* Set Attack component */
	owner_->AddComponent<Transform>();
	owner_->AddComponent<RigidBody>();
	owner_->AddComponent<BoxCollider>();
	owner_->AddComponent<Sprite>();

	owner_->GetComponent<Transform>()->SetScale({ 50, 50 });
	owner_->GetComponent<Sprite>()->SetColor({ 100, 200, 100 });
}

void MeleeAttack::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
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

void MeleeAttack::AttackObject(s32 x, s32 y)
{
	owner_->active_ = true;

	AEVec2 attackDir{ x - windowWidth / 2, windowHeight / 2 - y }, unitDir;
	AEVec2Normalize(&unitDir, &attackDir);

	attackDir = unitDir * range_ * 10.f;

	// collider 설정하고
	AEVec2 playerPos = player_->GetComponent<Transform>()->GetPosition();
	owner_->GetComponent<Transform>()->SetPosition(playerPos + attackDir);
}

ComponentSerializer* MeleeAttack::CreateComponent(GameObject* owner)
{
	return nullptr;
}
