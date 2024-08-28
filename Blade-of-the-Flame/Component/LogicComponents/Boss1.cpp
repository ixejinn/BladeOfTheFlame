#include "Boss1.h"

#include "../../GameObject/GameObject.h"

Boss1::Boss1(GameObject* owner) : BossComp(owner)
{
	hp_		    = 500;
	moveSpeed_  =   5;
	chaseSpeed_ =   6;
	baseDmg_    =   5;
	skillDmg_   =  10;
	range_		= 1.5;
}

void Boss1::Update()
{
	baseAttack();

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

void Boss1::baseAttack()
{
	
}

void Boss1::Phase1()
{

}

void Boss1::Phase2()
{

}

void Boss1::Phase3()
{

}