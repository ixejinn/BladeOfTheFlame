#include "petBullet.h"

#include "../../Event/Event.h"
#include "../Monster.h"
#include "../../Utils/Utils.h"

PB::PB(GameObject* owner) : BaseAttack(owner)
{
	goalPos = { 0, 0 };
	range_ = 80;
	lifetime = 12000;
	mode = set;
	dmg_ = 10;
	dmgGrowthRate_ = 5.f;
	owner_->AddComponent<Transform>();
	owner_->AddComponent<RigidBody>();
	owner_->AddComponent<Sprite>();
	owner->AddComponent<AnimationComp>();
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/1.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/2.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/3.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/4.png", "Attack");
	owner->GetComponent<AnimationComp>()->ChangeAnimation("Attack");
	owner->GetComponent<Transform>()->SetScale({ 20, 20 });

	owner_->AddComponent<BoxCollider>();
	BoxCollider* col = owner_->GetComponent<BoxCollider>();
	col->SetLayer(Collider::P_ATTACK);
	col->SetType(Collider::AABB_TYPE);
	col->SetHandler(static_cast<EventEntity*>(this));
}

PB::~PB()
{
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Transform>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<RigidBody>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Sprite>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<AnimationComp>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<BoxCollider>())));

	// GameObject »èÁ¦
	GameObjectManager::GetInstance().RemoveObject(owner_->GetName());
}


void PB::Update()
{
	if(mode == set)
	{
		AEVec2 attackDir{ goalPos - owner_->GetComponent<Transform>()->GetPosition() };
		AEVec2Normalize(&dir, &attackDir);
		owner_->GetComponent<Transform>()->SetRotation(dir);
		mode = fire;
	}
	if (mode == fire)
	{
		if (lifetime > 0)
		{
			float dt = AEFrameRateControllerGetFrameRate();
			lifetime -= dt;
			owner_->GetComponent<RigidBody>()->AddVelocity(dir * 300);
		}
		else
		{
			owner_->active_ = false;
			owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<PB>())));
		}
	}
}

void PB::LevelUp()
{
	dmg_ += int(dmg_ * dmgGrowthRate_ / 100);
}

void PB::AttackObject()
{
}

ComponentSerializer* PB::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<PB>())
		std::cout << "PB::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<PB>();
}

void PB::OnEvent(BaseEvent*)
{
}

void PB::OnCollision(CollisionEvent* event)
{
	Monster* monster = event->from_->GetComponent<Monster>();
	if (monster)
	{
		monster->ReserveDmg(dmg_);
		owner_->active_ = false;
		owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<PB>())));
	}

	Boss1* boss = event->from_->GetComponent<Boss1>();
	if (boss)
	{
		boss->ReserveDmg(dmg_);
		owner_->active_ = false;
		owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<PB>())));
	}
}

void PB::LoadFromJson(const json&)
{
}

json PB::SaveToJson()
{
	return json();
}