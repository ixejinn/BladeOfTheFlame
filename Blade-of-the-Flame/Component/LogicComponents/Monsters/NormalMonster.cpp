#include "NormalMonster.h"

#include <iomanip>	// std::setw, std::setfill
#include <sstream>	// std::stringstream
#include "../../../Manager/MonsterManager.h"
#include "../../../GameObject/GameObject.h"

namespace Manager
{
	extern GameObjectManager& objMgr;
	extern MonsterManager& monMgr;
}

NormalMonster::NormalMonster(GameObject* owner) : BaseMonster(owner)
{
	maxHp_ = hp_ = 20;
	exp_ = 5;
	dmg_ = 8;
	moveSpeed_ = 13.f;
	
	owner_->AddComponent<AnimationComp>();

	trans_->SetScale({ 30, 100 });

	BoxCollider* col = owner_->GetComponent<BoxCollider>();
	col->SetScale({ 0.8f, 0.7f });
	col->SetCenter({ -0.1f, -0.1f });

	SetAnimation();
}

void NormalMonster::Dead()
{
	hp_ = maxHp_;
	Manager::monMgr.Release(MonsterManager::NORMAL, owner_);
}

void NormalMonster::SetAnimation()
{
	ani_->AddAnimation("Walk");
	for (int i = 0; i <= 12; i++)
	{
		std::stringstream ss;
		ss << "Assets/Monster_anime/tile" << std::setw(3) << std::setfill('0') << i << ".png";
		std::string name = ss.str();
		ani_->AddDetail(name, "Walk");
	}
	ani_->SetTerm(200);

	ani_->ChangeAnimation("Walk");
}
