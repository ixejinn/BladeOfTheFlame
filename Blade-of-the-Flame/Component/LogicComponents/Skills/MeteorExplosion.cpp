#include "MeteorExplosion.h"
#include "Meteor.h"

class Meteor;

MeteorExplosion::MeteorExplosion(GameObject* owner) : BaseAttack(owner)
{
	meteorInf = GameObjectManager::GetInstance().GetObjectA("MeteorAttack");
	owner->GetComponent<Transform>()->SetPosition(meteorInf->GetComponent<Transform>()->GetPosition());
	lifetime = 3000;
	mode = set;
	dmg_ = meteorInf->GetComponent<Meteor>()->GetDmg();
	dmgGrowthRate_ = meteorInf->GetComponent<Meteor>()->GetDmgGrowRate();

}

void MeteorExplosion::Update()
{
	if (mode == set)
	{
		Ps = (meteorInf->GetComponent<Transform>()->GetPosition());
		mode = go;
	}
	if (mode == go)
	{
		if (lifetime > 0)
		{
			float df = AEFrameRateControllerGetFrameRate();
			lifetime -= df;
			owner_->GetComponent<Transform>()->SetPosition(Ps);
			// Animation
		}
		else
		{
			mode = set;
			lifetime = 3000;
			owner_->active_ = false;
		}
	}
}

void MeteorExplosion::LevelUp()
{
	dmg_ += int(dmg_ * dmgGrowthRate_ / 100);
}

void MeteorExplosion::AttackObject()
{
}

void MeteorExplosion::LoadFromJson(const json&)
{
}

json MeteorExplosion::SaveToJson()
{
	return json();
}
