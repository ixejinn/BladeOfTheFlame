#include "Boss1.h"
#include "../../Utils/MathUtils.h"
#include "../../Manager/GameObjectManager.h"

Boss1::Boss1(GameObject* owner) : BossComp(owner)
{
	hp_		    = 500;
	moveSpeed_  =   5;
	chaseSpeed_ =   3;
	baseDmg_    =   5;
	skillDmg_   =  10;
	range_		= 1.5;
	phaseTime_  = 0.0;
	phase1Time_ = 0.0;
}

void Boss1::Update()
{
	Transform* bossTrans = owner_->GetComponent<Transform>();
	if (!bossTrans)
		return;

	RigidBody* bossRb = owner_->GetComponent<RigidBody>();
	if (!bossRb)
		return;
	//if
	phaseTime_+= 0.1;

	BaseChase();

	if (hp_ >= 350)
	{
		Phase1();
	}
	if (hp_ <= 350 && hp_ >= 150)
	{
		Phase2();
	}
	if (hp_ <= 150)
	{
		Phase3();
	}
}

void Boss1::BossState()
{

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
