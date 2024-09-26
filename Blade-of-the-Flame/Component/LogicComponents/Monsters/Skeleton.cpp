#include "Skeleton.h"

#include <iomanip>	// std::setw, std::setfill
#include <sstream>	// std::stringstream
#include "../../../GameObject/GameObject.h"
#include "../../../Manager/ExpItemManager.h"
#include "../../../Manager/MonsterManager.h"

namespace Manager
{
	extern ExpItemManager& expMgr;
	extern MonsterManager& monMgr;
}

Skeleton::Skeleton(GameObject* owner) : BaseMonster(owner)
{
	maxHp_ = hp_ = 20;
	exp_ = 5;
	dmg_ = 8;
	moveSpeed_ = 10.f;
	
	owner_->AddComponent<AnimationComp>();

	trans_->SetScale({ 30, 100 });

	BoxCollider* col = owner_->GetComponent<BoxCollider>();
	col->SetScale({ 0.8f, 0.7f });
	col->SetCenter({ -0.1f, -0.1f });

	ani_ = owner_->GetComponent<AnimationComp>();
	sp_ = owner_->GetComponent<Sprite>();

	SetAnimation();
}

void Skeleton::Update()
{
	AEVec2 playerPos = playerTrans_->GetPosition();
	AEVec2 pos = trans_->GetPosition();
	AEVec2 moveDir = playerPos - pos, unitMoveDir;
	f32 squareDist = AEVec2SquareLength(&moveDir);

	int deadState = 0;	// -1: despawned, 0: alive, 1: dead
	if (hp_ <= 0)
	{
		ExpItem* expGem = Manager::expMgr.Spawn(pos);
		if (expGem)
			expGem->SetExp(exp_);
		deadState = 1;

		Manager::monMgr.AddCapturedCount();
	}
	else if (squareDist > 4 * windowWidth * windowWidth)
		deadState = -1;

	if (deadState != 0)
	{
		hp_ = maxHp_;
		Manager::monMgr.Release(owner_);
		return;
	}

	// Change velocity
	AEVec2 velocity = rb_->GetVelocity();
	f32 dotProduct = moveDir.x * velocity.x + moveDir.y * velocity.y;
	if (dotProduct < 0)
		rb_->ClearVelocity();

	AEVec2Normalize(&unitMoveDir, &moveDir);
	rb_->AddVelocity(unitMoveDir * moveSpeed_);

	// Change direction
	Direction curDir = unitMoveDir.x < 0 ? LEFT : RIGHT;
	if (dir_ != curDir)
		trans_->SetFlip();
	dir_ = curDir;

	// Change color to red briefly when attacked
	if (state_ == HURT)
		sp_->SetColor({ 255, 0, 0 });
	else
		sp_->SetColor({ 0, 0, 0 });
	state_ = MOVE;
}

void Skeleton::SetAnimation()
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
