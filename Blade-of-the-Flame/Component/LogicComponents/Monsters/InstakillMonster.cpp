#include "InstakillMonster.h"

#include <iomanip>	// std::setw, std::setfill
#include <sstream>	// std::stringstream
#include "../../../GameObject/GameObject.h"

InstakillMonster::InstakillMonster(GameObject* owner) : BaseMonster(owner)
{
	maxHp_ = hp_ = 200;
	exp_ = 50;
	dmg_ = 9999;
	moveSpeed_ = 3.f;

	owner_->AddComponent<AnimationComp>();

	trans_->SetScale({ 45, 150 });

	BoxCollider* col = owner_->GetComponent<BoxCollider>();
	col->SetScale({ 0.8f, 0.7f });
	col->SetCenter({ -0.1f, -0.1f });

	SetAnimation();
}

void InstakillMonster::SetAnimation()
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
