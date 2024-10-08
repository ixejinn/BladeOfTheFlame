#include "gtae.h"

#include "../../../Event/Event.h"
#include "../Monster.h"
#include "../../../Utils/Utils.h"

Gtae::Gtae(GameObject* owner) : BaseAttack(owner)
{
	mode = set;
	lifetime = 9000;
	range_ = 200;
	dmg_ = 1;
	tempdmg = dmg_;
	cooldown_ = 2000;
	dmgGrowthRate_ = 5.f;
	owner_->AddComponent<Transform>();
	owner_->AddComponent<RigidBody>();
	owner_->AddComponent<Sprite>();
	owner->AddComponent<AnimationComp>();
	for (int i = 0; i < 16; i++)
	{
		owner->GetComponent<AnimationComp>()->AddDetail("Assets/gtae__Anime/" + std::to_string(i) + ".png", "Attack");
	}
	owner->GetComponent<AnimationComp>()->ChangeAnimation("Attack");
	owner->GetComponent<AnimationComp>()->SetTerm(100);
	owner->GetComponent<Transform>()->SetScale({ 0, 0 });

	owner_->AddComponent<CircleCollider>();
	CircleCollider* col = owner_->GetComponent<CircleCollider>();
	col->SetLayer(Collider::P_ATTACK);
	col->SetType(Collider::OBB_TYPE);
	col->SetHandler(static_cast<EventEntity*>(this));
}

Gtae::~Gtae()
{
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Transform>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<RigidBody>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Sprite>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<AnimationComp>())));
	GameObjectManager::GetInstance().RemoveObject(owner_->GetName());
}

void Gtae::Update()
{
	float dt = AEFrameRateControllerGetFrameRate();
	if (mode == set)
	{
		dmg_ = 0;
		owner_->GetComponent<Transform>()->SetPosition(player_->GetComponent<Transform>()->GetPosition());
		AEInputInit();
		s32 x, y;
		AEInputGetCursorPosition(&x, &y);
		AEVec2 mousePosF({ static_cast<float>(x), static_cast<float>(y) });
		if (!AEInputCheckCurr(AEVK_LBUTTON))
		{
			AEVec2 attackDir{ convert(mousePosF) - owner_->GetComponent<Transform>()->GetPosition() };
			AEVec2Normalize(&dir, &attackDir);
			owner_->GetComponent<Transform>()->SetScale({ 200, 200 });
			owner_->GetComponent<Transform>()->SetRotation(dir);
			mode = fire;
			dmg_ = tempdmg;
			owner_->GetComponent<RigidBody>()->AddVelocity(dir * 850);
		}
	}
	if (mode == fire)
	{
		if (lifetime > 0)
		{
			lifetime -= dt;
		}
		else
		{
			owner_->active_ = false;
			owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Gtae>())));
		}
	}
}

void Gtae::LevelUp()
{
	tempdmg += int(tempdmg * dmgGrowthRate_ / 100);
}

void Gtae::AttackObject()
{
}

ComponentSerializer* Gtae::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Gtae>())
		std::cout << "Gtae::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Gtae>();
}

void Gtae::OnEvent(BaseEvent*)
{
}

void Gtae::OnCollision(CollisionEvent* event)
{
	Monster* monster = event->from_->GetComponent<Monster>();
	if (monster)
	{
		player_->GetComponent<Player>()->SkillGage += 0.05;
		monster->ReserveDmg(dmg_);
		monster->state_ = monster->HURT;
	}

	Boss1* boss = event->from_->GetComponent<Boss1>();
	if (boss)
	{
		player_->GetComponent<Player>()->SkillGage += 0.05;
		boss->ReserveDmg(dmg_);
	}
}

void Gtae::LoadFromJson(const json&)
{
}

json Gtae::SaveToJson()
{
	return json();
}
