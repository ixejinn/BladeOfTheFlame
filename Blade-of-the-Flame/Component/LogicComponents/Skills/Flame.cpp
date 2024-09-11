#include "Flame.h"
#include "../../Event/Event.h"
#include "../Monster.h"


Flame::Flame(GameObject* owner) : BaseAttack(owner)
{
	mode = set;
	lifetime = 12000;
	dmg_ = 10;
	cooldown_ = 1;
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
	owner->GetComponent<Transform>()->SetScale({80, 50});

	owner_->AddComponent<BoxCollider>();
	BoxCollider* col = owner_->GetComponent<BoxCollider>();
	col->SetLayer(Collider::P_ATTACK);
	col->SetType(Collider::AABB_TYPE);
	col->SetHandler(static_cast<EventEntity*>(this));
}

Flame::~Flame()
{
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Transform>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<RigidBody>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Sprite>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<AnimationComp>())));
	GameObjectManager::GetInstance().RemoveObject(owner_->GetName());
}

namespace
{
	AEVec2 convert(AEVec2 a)
	{
		AEVec2 worldPos;
		worldPos.x = a.x - windowWidth / 2;
		worldPos.y = -a.y + windowHeight / 2;
		AEVec2 pos;
		AEGfxGetCamPosition(&pos.x, &pos.y);
		AEVec2 result;
		result.x = worldPos.x + pos.x;
		result.y = worldPos.y + pos.y;
		return result;
	}
}

void Flame::Update()
{
	if (mode == set)
	{
		owner_->GetComponent<Transform>()->SetPosition(player_->GetComponent<Transform>()->GetPosition());
		AEInputInit();
		s32 x, y;
		AEInputGetCursorPosition(&x, &y);
		AEVec2 mousePosF({ static_cast<float>(x), static_cast<float>(y) });
		if (!AEInputCheckCurr(AEVK_LBUTTON))
		{
			AEVec2 attackDir{ convert(mousePosF) - owner_->GetComponent<Transform>()->GetPosition() };
			AEVec2Normalize(&dir, &attackDir);
			owner_->GetComponent<Transform>()->SetRotation(dir);
			player_->GetComponent<Player>()->flameCool = 0;
			mode = fire;
		}
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
			owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Flame>())));
		}
	}
}

void Flame::LevelUp()
{
	dmg_ += int(dmg_ * dmgGrowthRate_ / 100);
}

void Flame::AttackObject()
{
}

ComponentSerializer* Flame::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Flame>())
		std::cout << "Flame::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Flame>();
}

void Flame::OnEvent(BaseEvent*)
{
}

void Flame::OnCollision(CollisionEvent* event)
{
	Monster* monster = event->from_->GetComponent<Monster>();
	if (monster)
	{
		monster->ReserveDmg(dmg_);
		owner_->active_ = false;
		owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Flame>())));
	}
}

void Flame::LoadFromJson(const json&)
{
}

json Flame::SaveToJson()
{
	return json();
}
