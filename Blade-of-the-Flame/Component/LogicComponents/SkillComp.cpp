#include "SkillComp.h"
#include "Skills/Meteor.h"
#include "Player.h"
#include "AEEngine.h"
#include "../../GameObject/GameObject.h"

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
	if (Qactive == true)
	{
		if (Eactive == true && owner_->GetComponent<Player>()->GetLevel() >= 4)
		{
			if (Ractive == true && owner_->GetComponent<Player>()->GetLevel() >= 7)//QER
			{
				type = cInferno;
			}
			else//QE
			{
				type = cFireball;
			}
		}
		else if (Ractive == true && owner_->GetComponent<Player>()->GetLevel() >= 5)//QR
		{
			type = cEating_Oxyzen;
		}
		else//Q
		{
			type = cScorching;
		}
	}
	else if (Eactive == true && owner_->GetComponent<Player>()->GetLevel() >= 2)
	{
		if (Ractive == true && owner_->GetComponent<Player>()->GetLevel() >= 6)//ER
		{
			type = cMeteor;
		}
		else//E
		{
			type = cFlame;
		}
	}
	else if (Ractive == true && owner_->GetComponent<Player>()->GetLevel() >= 3)//R
	{
		type = cHaste;
	}
	else
		type = Default;
}

void SkillComp::Update()
{
	float dt = AEFrameRateControllerGetFrameRate();
	if (CoolTime > 0)
	{
		CoolTime -= dt;
	}
	if (CoolTime <= 0)
	{
		KeyCheck();
		SetSkillType();

		auto it = allSkill.find(type);
		it->second();
	}
}

void SkillComp::Scorching_Update()
{
	CoolTime = 2000;
}

void SkillComp::Flame_Update()
{
	CoolTime = 2000;
}

void SkillComp::Haste_Update()
{
	CoolTime = 15000;
}

void SkillComp::Fireball_Update()
{
	CoolTime = 10000;
}

void SkillComp::Eating_Oxyzen_Update()
{
	CoolTime = 10000;
}

void SkillComp::Meteor_Update()
{
	owner_->GetComponent<Meteor>()->onoff = true;
	if (owner_->GetComponent<Meteor>()->onoff == false)
	{
		CoolTime = 30000;
	}
}

void SkillComp::Inferno_Update()
{
	CoolTime = 50000;
}

void SkillComp::Default_Update()
{
}

SkillComp::SkillComp(GameObject* owner) : LogicComponent(owner)
{
	allSkill.emplace(cScorching, Scorching_Update);
	allSkill.emplace(cFlame, Flame_Update);
	allSkill.emplace(cHaste, Haste_Update);
	allSkill.emplace(cFireball, Fireball_Update);
	allSkill.emplace(cEating_Oxyzen, Eating_Oxyzen_Update);
	allSkill.emplace(cMeteor, Meteor_Update);
	allSkill.emplace(cInferno, Inferno_Update);
	allSkill.emplace(Default, Default_Update);
}

SkillComp::~SkillComp()
{

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
