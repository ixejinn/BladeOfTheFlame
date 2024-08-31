#include "SkillComp.h"

#include "AEEngine.h"
#include "../GameObject/GameObject.h"

void SkillComp::KeyCheck()
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
void SkillComp::SetSkillType()
{
	//if (Qactive == true)
	//{
	//	if (Eactive == true && owner_->GetComponent<PlayerComp>().getlevel() >= 4)
	//	{
	//		if (Ractive == true && owner_->GetComponent<PlayerComp>().getlevel() >= 7)//QER
	//		{
	//			type = Inferno;
	//		}
	//		else//QE
	//		{
	//			type = Fireball;
	//		}
	//	}
	//	else if (Ractive == true && owner_->GetComponent<PlayerComp>().getlevel() >= 5)//QR
	//	{
	//		type = Eating_Oxyzen;
	//	}
	//	else//Q
	//	{
	//		type = Scorching;
	//	}
	//}
	//else if (Eactive == true && owner_->GetComponent<PlayerComp>().getlevel() >= 2)
	//{
	//	if (Ractive == true && owner_->GetComponent<PlayerComp>().getlevel() >= 6)//ER
	//	{
	//		type = Meteor;
	//	}
	//	else//E
	//	{
	//		type = Flame;
	//	}
	//}
	//else if (Ractive == true && owner_->GetComponent<PlayerComp>().getlevel() >= 3)//R
	//{
	//	type = Haste;
	//}
	//else
	//	type = Default;
}

void SkillComp::Scorching_Update()
{
}

void SkillComp::Flame_Update()
{
}

void SkillComp::Haste_Update()
{
}

void SkillComp::Fireball_Update()
{
}

void SkillComp::Eating_Oxyzen_Update()
{
}

void SkillComp::Meteor_Update()
{
}

void SkillComp::Inferno_Update()
{
}

SkillComp::SkillComp(GameObject* owner) : LogicComponent(owner)
{

}

SkillComp::~SkillComp()
{

}

void SkillComp::Update()
{
	KeyCheck();
}

void SkillComp::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void SkillComp::LoadFromJson(const json&)
{
}

json SkillComp::SaveToJson()
{
	return json();
}

ComponentSerializer* SkillComp::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<SkillComp>())
		std::cout << "Sprite::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<SkillComp>();
}
