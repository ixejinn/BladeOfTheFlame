#include "SkillManager.h"
#include "../Component/LogicComponents/Skills/Meteor.h"
#include "../Component/LogicComponents/Player.h"
#include "AEEngine.h"
//#include "../../GameObject/GameObject.h"
#include "../GameObject/GameObject.h"

void SkillManager::KeyCheck()
{
	if (AEInputCheckTriggered(AEVK_Q))
	{
		if (Qactive == false)
			Qactive = true;
		else
			Qactive = false;
	}
	if (AEInputCheckTriggered(AEVK_E))
	{
		if (Eactive == false)
			Eactive = true;
		else
			Eactive = false;
	}
	if (AEInputCheckTriggered(AEVK_R))
	{
		if (Ractive == false)
			Ractive = true;
		else
			Ractive = false;
	}
}

void SkillManager::SetSkillType(int level)
{
	static int prev_type = type;
	prev_type = type;

	//std::cout << AEFrameRateControllerGetFrameCount() << " " << Qactive << " " << Ractive << " " << Eactive << std::endl << std::endl;
	
	if (Qactive == true)
	{
		if (Eactive == true && level >= 4)
		{
			if (Ractive == true && level >= 7)//QER
			{
				type = cInferno;
			}
			else//QE
			{
				type = cFireball;
			}
		}
		else if (Ractive == true && level >= 5)//QR
		{
			type = cEating_Oxyzen;
		}
		else//Q
		{
			type = cScorching;
		}
	}
	else if (Eactive == true && level >= 2)
	{
		if (Ractive == true && level >= 6)//ER
		{
			type = cMeteor;
		}
		else//E
		{
			type = cFlame;
		}
	}
	else if (Ractive == true && level >= 3)//R
	{
		type = cHaste;
	}
	else
		type = Default;

	if (type != prev_type)
	{
		std::cout << "changed to " << type << " from " << prev_type << std::endl;
	}
}

SkillManager::SkillManager()
{

}

SkillManager::~SkillManager()
{

}