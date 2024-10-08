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
	owner->AddComponent<AnimationComp>();
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			owner->GetComponent<AnimationComp>()->AddDetail("Assets/MeteorAnime/explosion/tile0" + std::to_string(j) + std::to_string(i) + ".png", "Attack");
		}
	}	
	for (int i = 0; i < 8; i++)
	{
		owner->GetComponent<AnimationComp>()->AddDetail("Assets/MeteorAnime/explosion/tile04" + std::to_string(i) + ".png", "Attack");
	}
	owner->GetComponent<AnimationComp>()->SetTerm(100.f);
	owner_->GetComponent<AnimationComp>()->ChangeAnimation("Attack");

	owner->GetComponent<Transform>()->SetPosition(player_->GetComponent<Transform>()->GetPosition());
	lifetime = 3000;
	mode = set;
	owner->GetComponent<Transform>()->SetScale({ 900, 900 });

	//**//
	owner_->AddComponent<CircleCollider>();
	CircleCollider* col = owner_->GetComponent<CircleCollider>();
	col->SetLayer(Collider::P_ATTACK);
	col->SetType(Collider::AABB_TYPE);
	col->SetHandler(static_cast<EventEntity*>(this));
	col->SetRadius(100);

	//dmg_ = 20;
	dmg_ = 3;
	dmgGrowthRate_ = 10.f;
}

void MeteorExplosion::Update()
{
	if (mode == set)
	{
		Ps = (player_->GetComponent<Transform>()->GetPosition());
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

	Boss1* boss = event->from_->GetComponent<Boss1>();
	if (boss)
	{
		boss->ReserveDmg(dmg_);
	}
}

ComponentSerializer* MeteorExplosion::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<MeteorExplosion>())
		std::cout << "MeteorExplosion::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<MeteorExplosion>();
}
