#include "grab.h"

#include "../../Event/Event.h"
#include "../Monster.h"
#include "../../Utils/Utils.h"

Grab::Grab(GameObject* owner) : BaseAttack(owner)
{
	mode = set;
	lifetime = 9000;
	range_ = 500;
	dmg_ = 0.05;
	tempdmg = dmg_;
	cooldown_ = 2000;
	dmgGrowthRate_ = 5.f;
	owner_->AddComponent<Transform>();
	owner_->AddComponent<RigidBody>();
	owner_->AddComponent<Sprite>();
	owner->AddComponent<AnimationComp>();
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/grab.png", "Attack");
	owner->GetComponent<AnimationComp>()->ChangeAnimation("Attack");
	owner->GetComponent<AnimationComp>()->SetTerm(1000);
	owner->GetComponent<Transform>()->SetScale({ 0, 0 });

	owner_->AddComponent<CircleCollider>();
	CircleCollider* col = owner_->GetComponent<CircleCollider>();
	col->SetLayer(Collider::P_ATTACK);
	col->SetType(Collider::OBB_TYPE);
	col->SetHandler(static_cast<EventEntity*>(this));
}

Grab::~Grab()
{
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Transform>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<RigidBody>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Sprite>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<AnimationComp>())));
	GameObjectManager::GetInstance().RemoveObject(owner_->GetName());
}

void Grab::Update()
{
	float dt = AEFrameRateControllerGetFrameRate();
	if (mode == set)
	{
		lifetime = 9000;
		dmg_ = 0;
		AEInputInit();
		s32 x, y;
		AEInputGetCursorPosition(&x, &y);
		AEVec2 mousePosF({ static_cast<float>(x), static_cast<float>(y) });
		if (!AEInputCheckCurr(AEVK_LBUTTON))
		{
			owner_->GetComponent<Transform>()->SetPosition(player_->GetComponent<Transform>()->GetPosition());
			AEVec2 attackDir{ convert(mousePosF) - owner_->GetComponent<Transform>()->GetPosition() };
			AEVec2Normalize(&dir, &attackDir);
			owner_->GetComponent<Transform>()->SetScale({ range_, range_ });
			owner_->GetComponent<Transform>()->SetRotation(dir);
			mode = fire;
			dmg_ = tempdmg;
			owner_->GetComponent<RigidBody>()->AddVelocity(dir * 3000);
			player_->GetComponent<Player>()->SkillGage = 0;
		}
	}
	if (mode == fire)
	{
		if (lifetime > 0)
		{
			lifetime -= dt;
			owner_->GetComponent<Transform>()->SetRotation(owner_->GetComponent<Transform>()->GetRotation() + dt/20);
		}
		else
		{
			mode = set;
			owner_->active_ = false;
		}
	}
}

void Grab::LevelUp()
{
	tempdmg += int(tempdmg * dmgGrowthRate_ / 100);
}

void Grab::AttackObject()
{
}

ComponentSerializer* Grab::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Grab>())
		std::cout << "Grab::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Grab>();
}

void Grab::OnEvent(BaseEvent*)
{
}

void Grab::OnCollision(CollisionEvent* event)
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

void Grab::LoadFromJson(const json&)
{
}

json Grab::SaveToJson()
{
	return json();
}
