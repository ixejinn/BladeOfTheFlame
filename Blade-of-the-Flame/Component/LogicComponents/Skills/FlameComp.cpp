#include "FlameComp.h"
#include "Flame.h"
//#include "../../Event/Event.h"
#include "../../../Event/Event.h"
#include "../Monster.h"
FlameComp::FlameComp(GameObject* owner) : BaseAttack(owner)
{
	lifetime = 12000;
	owner_->AddComponent<Transform>();
	owner_->AddComponent<RigidBody>();
	owner_->AddComponent<Sprite>();
	owner->AddComponent<AnimationComp>();
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/1.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/2.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/3.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/4.png", "Attack");
	owner->GetComponent<AnimationComp>()->ChangeAnimation("Attack");
	flameInf = GameObjectManager::GetInstance().GetObjectA("FlameAttack");
	dir = flameInf->GetComponent<Flame>()->GetUnitDir();
	owner->GetComponent<Transform>()->SetScale({80, 50});
	mode = set;

	owner_->AddComponent<BoxCollider>();
	BoxCollider* col = owner_->GetComponent<BoxCollider>();
	col->SetLayer(Collider::P_ATTACK);
	col->SetType(Collider::AABB_TYPE);
	col->SetHandler(static_cast<EventEntity*>(this));

	dmg_ = flameInf->GetComponent<Flame>()->GetDmg();
	dmgGrowthRate_ = flameInf->GetComponent<Flame>()->GetDmgGrowRate();
}

void FlameComp::Update()
{
	if (mode == set)
	{
		owner_->GetComponent<Transform>()->SetPosition(player_->GetComponent<Transform>()->GetPosition());
		owner_->GetComponent<Transform>()->SetRotation(dir);
		mode = go;
	}
	if (mode == go)
	{
		if (lifetime > 0)
		{
			float df = AEFrameRateControllerGetFrameRate();
			lifetime -= df;
			owner_->GetComponent<RigidBody>()->AddVelocity(dir * 300);
		}
		else
		{
			mode = set;
			lifetime = 12000;
			owner_->active_ = false;
		}
	}
}

void FlameComp::LevelUp()
{
	dmg_ += int(dmg_ * dmgGrowthRate_ / 100);
}

void FlameComp::AttackObject()
{
}

ComponentSerializer* FlameComp::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<FlameComp>())
		std::cout << "FlameComp::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<FlameComp>();
}

void FlameComp::OnEvent(BaseEvent*)
{
}

void FlameComp::OnCollision(CollisionEvent* event)
{
	Monster* monster = event->from_->GetComponent<Monster>();
	if (monster)
	{
		monster->ReserveDmg(dmg_);
	}
}

void FlameComp::LoadFromJson(const json&)
{
}

json FlameComp::SaveToJson()
{
	return json();
}
