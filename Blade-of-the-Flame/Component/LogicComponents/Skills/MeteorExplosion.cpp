#include "MeteorExplosion.h"
#include "Meteor.h"
//**//
#include "../../../Event/Event.h"
#include "../Monster.h"

class Meteor;

MeteorExplosion::MeteorExplosion(GameObject* owner) : BaseAttack(owner)
{
	owner->AddComponent<Transform>();
	owner->AddComponent<RigidBody>();
	owner->AddComponent<Sprite>();
	meteorInf = GameObjectManager::GetInstance().GetObjectA("MeteorAttack");
	owner->GetComponent<Transform>()->SetPosition(meteorInf->GetComponent<Transform>()->GetPosition());
	lifetime = 3000;
	mode = set;
	owner->GetComponent<Transform>()->SetScale({ 300, 300 });
	owner->GetComponent<Sprite>()->SetColor({ 255, 0, 0 });

	//**//
	owner_->AddComponent<CircleCollider>();
	CircleCollider* col = owner_->GetComponent<CircleCollider>();
	col->SetLayer(Collider::P_ATTACK);
	col->SetType(Collider::CIRCLE_TYPE);
	col->SetHandler(static_cast<EventEntity*>(this));

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
//**//
void MeteorExplosion::OnEvent(BaseEvent*)
{
}

void MeteorExplosion::OnCollision(CollisionEvent* event)
{
	Monster* monster = event->from_->GetComponent<Monster>();
	if (monster)
	{
		monster->ReserveDmg(dmg_);
	}
}

ComponentSerializer* MeteorExplosion::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<MeteorExplosion>())
		std::cout << "MeteorExplosion::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<MeteorExplosion>();
}
