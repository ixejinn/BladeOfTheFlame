#include "Boss1.h"
#include "../../Utils/MathUtils.h"
#include "../../Manager/GameObjectManager.h"

Boss1::Boss1(GameObject* owner) : BossComp(owner)
{
	hp_		     = 500;
	moveSpeed_   =   1;
	chaseSpeed_  =  10;
	baseDmg_     =   5;
	skillDmg_    =  10;
	range_		 = 1.5;
	phaseTime_   = 0.0;

	current_state = Normal;
}

void Boss1::Update()
{
	Transform* bossTrans = owner_->GetComponent<Transform>();
	if (!bossTrans)
		return;

	RigidBody* bossRb = owner_->GetComponent<RigidBody>();
	if (!bossRb)
		return;

	// change current state accordingly
	BossState();

	if (current_state == Normal)
	{
		BaseChase();
	}
	else if (current_state == FastChase)
	{
		Phase1();
	}
}

void Boss1::BossState()
{
	const float normal_phase_time = 3;
	const float fastchase_phase_time = 6;
	const float faastchase_end_time = normal_phase_time + fastchase_phase_time;

	phaseTime_ += 0.016f; //delta time

	if (phaseTime_ < normal_phase_time)
	{
		current_state = Normal;
	}
	else if (phaseTime_ >= normal_phase_time && phaseTime_ < faastchase_end_time)
	{
		current_state = FastChase;
	}
	else if (phaseTime_ >= faastchase_end_time)
	{
		phaseTime_ = 0;
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

	bossRb->AddVelocity(unitChaseVec * chaseSpeed_);
}

void Boss1::Phase2()
{
	Transform* bossTrans = owner_->GetComponent<Transform>();
	RigidBody* bossRb = owner_->GetComponent<RigidBody>();
	AEVec2     playerPos = player->GetComponent<Transform>()->GetPosition();
	
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
