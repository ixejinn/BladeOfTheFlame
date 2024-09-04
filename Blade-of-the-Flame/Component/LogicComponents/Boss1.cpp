#include "Boss1.h"
#include "../../Utils/MathUtils.h"
#include "../../Manager/GameObjectManager.h"
Boss1::Boss1(GameObject* owner) : BossComp(owner)
{
	hp_		     = 500;
	moveSpeed_   =   5;
	chaseSpeed_  =  30;
	baseDmg_     =   5;
	skillDmg_    =  10;
	range_		 = 1.5;

	nomalphaseTime_    = 0.0;

	phase1Count_ = 0;
	phase2Count_ = 0;

	current_state = Normal;
	phaseOn = false;
	needShoot = true;
	

}

void Boss1::Update()
{
	//Transform* bossTrans = owner_->GetComponent<Transform>();
	//if (!bossTrans)
	//	return;
	//
	//RigidBody* bossRb = owner_->GetComponent<RigidBody>();
	//if (!bossRb)
	//	return;
	//BaseChase();

	Phase2();	

	//BossState();
	
	//if (current_state == Normal)
	//{
	//	BaseChase();
	//}
	//else if (current_state == FastChase)
	//{
	//	Phase1();
	//}
	//else if (current_state == RangeAttack)
	//{
	//	Phase2();
	//}
	//else if (current_state == Barrage)
	//{
	//	Phase3();
	//}
}

void Boss1::BossState()
{
	const float normal_phase_time = 5;
	const float fastchase_phase_time = 1;
	const float fastchase_end_time = normal_phase_time + fastchase_phase_time;

	nomalphaseTime_ += AEFrameRateControllerGetFrameTime(); //delta time

	if (nomalphaseTime_ < normal_phase_time)
	{
		current_state = Normal;
	}
	else if (nomalphaseTime_ >= normal_phase_time && 
		     nomalphaseTime_ < fastchase_end_time && phaseOn == false) //phase1
	{
		current_state = FastChase;
		phaseOn = true;
	}
	else if (phase1Count_ == 1 && phaseOn == true) //phase2
	{
		current_state = RangeAttack;
	}
	else if (phase2Count_ == 2) //phase3
	{
		current_state = Barrage;
	}
	else if (nomalphaseTime_ >= fastchase_end_time)
	{
		nomalphaseTime_ = 0;
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
	if (phase1Count_ > 3)
	{
		phase1Count_ = 0; 
	}
	else
	{
		phase1Count_ += 1;
	}

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
	//if (phase2Count_ > 1)
	//{
	//	phase2Count_ = 0;
	//}
	//else
	//{
	//	phase2Count_ += 1;
	//}
	// 
	//Transform* bossTrans = owner_->GetComponent<Transform>();
	//RigidBody* bossRb = owner_->GetComponent<RigidBody>();
	//bullet->GetComponent<BulletComp>()->
	//if()
	
	if (needShoot || AEInputCheckCurr(AEVK_SPACE))
	{
		CreateBulletObj()->GetComponent<BulletComp>()->FireBullet();
		
		needShoot = false;
	}
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
