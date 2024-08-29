#include "Boss1.h"
#include "../../Utils/MathUtils.h"
#include "../../Manager/GameObjectManager.h"

Boss1::Boss1(GameObject* owner) : BossComp(owner)
{
	hp_		    = 500;
	moveSpeed_  =   3;
	chaseSpeed_ =   3;
	baseDmg_    =   5;
	skillDmg_   =  10;
	range_		= 1.5;

	phaseTime_  = 0.0;
	phase1Time_ = 0.0;

	phase1_ = false;
	phase2_ = false;
	phase3_ = false;
	phaseStart_ = true;
}

void Boss1::Update()
{
	Transform* bossTrans = owner_->GetComponent<Transform>();
	if (!bossTrans)
		return;

	RigidBody* bossRb = owner_->GetComponent<RigidBody>();
	if (!bossRb)
		return;

	BossState();
}

void Boss1::BossState()
{
	if (phaseStart_)
	{
		BaseChase();

		if (!phase1_ && phaseTime_ < 3.f)
		{
			Phase1();
			phaseTime_ += 0.1f;
			phase1_ = true;
		}
		else if(phase1_ && phaseTime_ < 6.f)
		{
			moveSpeed_ = 1.f;
			phaseTime_ = 0;
			phase1_ = false;
		}
	}
}

void Boss1::BaseChase()
{
	Transform* bossTrans = owner_->GetComponent<Transform>();
	RigidBody* bossRb	 = owner_->GetComponent<RigidBody>();

	AEVec2     playerPos = player->GetComponent<Transform>()->GetPosition();
	AEVec2	   bossPos   = bossTrans->GetPosition();

	AEVec2	   chaseVec = playerPos - bossPos;

	AEVec2	   unitChaseVec;

	AEVec2Normalize(&unitChaseVec, &chaseVec);

	bossRb->AddVelocity(unitChaseVec * moveSpeed_);
}

void Boss1::Phase1()
{
	Transform* bossTrans = owner_->GetComponent<Transform>();
	RigidBody* bossRb = owner_->GetComponent<RigidBody>();

	AEVec2     playerPos = player->GetComponent<Transform>()->GetPosition();
	AEVec2	   bossPos = bossTrans->GetPosition();

	AEVec2	   chaseVec = playerPos - bossPos;
	AEVec2	   unitChaseVec;
	
	AEVec2Normalize(&unitChaseVec, &chaseVec);

	moveSpeed_ = 6.f;
	bossRb->AddVelocity(unitChaseVec * moveSpeed_);
}

void Boss1::Phase2()
{
	Transform* bossTrans = owner_->GetComponent<Transform>();
	RigidBody* bossRb = owner_->GetComponent<RigidBody>();

}

void Boss1::Phase3()
{
	Transform* bossTrans = owner_->GetComponent<Transform>();
	RigidBody* bossRb = owner_->GetComponent<RigidBody>();

}

void Boss1::LoadFromJson(const json&)
{

}

json Boss1::SaveToJson()
{
	return json();
}
