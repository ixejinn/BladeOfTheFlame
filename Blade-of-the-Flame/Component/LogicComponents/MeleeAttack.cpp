#include "MeleeAttack.h"

#include "AEVec2.h"
#include "../../Event/Event.h"
#include "../../Manager/EventManager.h"
#include "../../Manager/GameObjectManager.h"

MeleeAttack::MeleeAttack(GameObject* owner) : BaseAttack(owner)
{
	dmg_ = 3;
	dmgGrowthRate_ = 50.f;

	range_ = 100.f;
	cooldown_ = 480.f;

	/* SET COMPONENTS */
	owner_->AddComponent<BoxCollider>();

	BoxCollider* col = owner_->GetComponent<BoxCollider>();
	col->SetType(Collider::OBB_TYPE);
	col->SetLayer(Collider::P_ATTACK);

	Transform* trans = owner_->GetComponent<Transform>();
	trans->SetScale({ range_, range_ });

	aniObj_ = GameObjectManager::GetInstance().CreateObject("meleeAni");
	aniObj_->AddComponent<Transform>();
	aniObj_->AddComponent<AnimationComp>();

	aniObj_->GetComponent<Transform>()->SetScale({ range_, range_ });

	AnimationComp* ani = aniObj_->GetComponent<AnimationComp>();
	ani->AddAnimation("Attack");
	for (int i = 1; i < 4; i++)
		ani->AddDetail("Assets/meleeAnime/" + std::to_string(i) + ".png", "Attack");
	ani->ChangeAnimation("Attack");
	ani->SetTerm(100);

	aniObj_->active_ = false;
}

void MeleeAttack::Update()
{
	static bool aniStart = true;
	static bool aniProgress = false;

	if (aniStart)
	{
		aniObj_->active_ = true;

		aniStart = false;
		aniProgress = true;

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
	}
	else if (aniProgress)
	{
		Transform* trans = owner_->GetComponent<Transform>();
		Transform* transAni = aniObj_->GetComponent<Transform>();
		transAni->SetPosition(trans->GetPosition());
		transAni->SetRotation(trans->GetRotation());

		if (aniObj_->GetComponent<AnimationComp>()->CurrentAnimationOver())
		{
			aniObj_->active_ = false;
			aniProgress = false;
			aniStart = true;

			owner_->active_ = false;
		}
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
}

ComponentSerializer* MeleeAttack::CreateComponent(GameObject* owner)
{
	return nullptr;
}
