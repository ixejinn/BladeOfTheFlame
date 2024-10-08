#include "BaseMonster.h"

#include "AEVec2.h"
#include "../Items/ExpItem.h"
#include "../../../Manager/ComponentManager.h"
#include "../../../Manager/GameObjectManager.h"
#include "../../../Manager/ExpItemManager.h"
#include "../../../Manager/MonsterManager.h"
#include "../../../Event/Event.h"
#include "../Skills/shield.h"
#include "../Skills/Flame.h"
#include "../Skills/doubleFlameL.h"
#include "../Skills/doubleFlameR.h"

namespace Manager
{
	extern GameObjectManager& objMgr;
	extern ExpItemManager& expMgr;
	extern MonsterManager& monMgr;
}

int BaseMonster::CheckDeadState(const AEVec2& pos, const f32& squareDist)
{
	int deadState = 0;	// -1: despawned, 0: alive, 1: dead
	if (hp_ <= 0)
	{
		rb_->ClearVelocity();

		ExpItem* expGem = Manager::expMgr.Spawn(pos);
		if (expGem)
			expGem->SetExp(exp_);
		deadState = 1;

		Manager::monMgr.AddCapturedCount();
	}
	else if (squareDist > 4 * windowWidth * windowWidth)
		deadState = -1;

	return deadState;
}

void BaseMonster::MoveToPlayer(AEVec2& moveDir)
{
	AEVec2 velocity = rb_->GetVelocity();
	
	AEVec2 unitMoveDir;
	AEVec2Normalize(&unitMoveDir, &moveDir);
	rb_->AddVelocity(unitMoveDir * moveSpeed_);

	// Change direction
	Direction curDir = unitMoveDir.x < 0 ? LEFT : RIGHT;
	if (dir_ != curDir)
		trans_->SetFlip();
	dir_ = curDir;
}

BaseMonster::BaseMonster(GameObject* owner) : LogicComponent(owner)
{
	knockback_ = 5.f;

	cooldown_ = 1.0;
	timeStart_ = std::chrono::system_clock::now();

	/* Set components */
	owner_->AddComponent<BoxCollider>();
	owner_->AddComponent<AnimationComp>();

	BoxCollider* col = owner_->GetComponent<BoxCollider>();
	col->SetLayer(Collider::E_BODY);
	col->SetHandler(static_cast<EventEntity*>(this));

	/* Set pointers */
	owner_->monsterPtr_ = this;

	trans_ = owner_->GetComponent<Transform>();
	rb_ = owner_->GetComponent<RigidBody>();
	ani_ = owner_->GetComponent<AnimationComp>();
	sp_ = owner_->GetComponent<Sprite>();

	playerTrans_ = Manager::objMgr.GetObjectA("player")->GetComponent<Transform>();
}

void BaseMonster::Update()
{
	AEVec2 playerPos = playerTrans_->GetPosition();
	AEVec2 pos = trans_->GetPosition();
	AEVec2 moveDir = playerPos - pos;
	f32 squareDist = AEVec2SquareLength(&moveDir);

	if (CheckDeadState(pos, squareDist) != 0)
	{
		Dead();
		return;
	}

	MoveToPlayer(moveDir);

	// Change color to red briefly when attacked
	if (state_ == HURT)
		sp_->SetColor({ 255, 0, 0 });
	else
		sp_->SetColor({ 0, 0, 0 });
	state_ = MOVE;
}

void BaseMonster::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void BaseMonster::LoadFromJson(const json&)
{
}

json BaseMonster::SaveToJson()
{
	return json();
}

void BaseMonster::OnEvent(BaseEvent* event)
{
}

void BaseMonster::OnCollision(CollisionEvent* event)
{
	BaseAttack* pAttack = event->ptom;
	if (pAttack)
	{
		hp_ -= pAttack->GetDmg();
		std::cout << hp_ << " " << pAttack->GetDmg() << std::endl;
		Manager::objMgr.GetObjectA("player")->GetComponent<Player>()->SkillGage += 1;

		if (hp_ > 0)
		{
			if (dynamic_cast<MeleeAttack*>(pAttack))
			{
				AEVec2 velocity = rb_->GetVelocity();
				AEVec2 playerPos = playerTrans_->GetPosition();
				AEVec2 pos = trans_->GetPosition();
				AEVec2 direction = playerPos - pos;
				f32 dotProduct = AEVec2DotProduct(&velocity, &direction);
				if (dotProduct > 0)
					rb_->SetVelocity(velocity * -knockback_);
			}

			state_ = HURT;
		}

		if (dynamic_cast<Flame*>(pAttack) ||
			dynamic_cast<doubleFlameL*>(pAttack) ||
			dynamic_cast<doubleFlameR*>(pAttack))
			event->from_->active_ = false;

		return;
	}

	BaseMonster* monster = event->monster;
	if (monster)
	{
		AEVec2 pos = trans_->GetPosition();
		AEVec2 otherPos = event->from_->GetComponent<Transform>()->GetPosition();

		AEVec2 dir = pos - otherPos, unitDir;
		AEVec2Normalize(&unitDir, &dir);

		rb_->AddVelocity(unitDir * moveSpeed_);

		return;
	}
}
