#include "boomerang.h"

#include "../../../Event/Event.h"
#include "../../../Manager/EventManager.h"
#include "../Monster.h"


boomerang::boomerang(GameObject* owner) : BaseAttack(owner)
{
	mode = set;
	rotationSpeed_ = 0.1;
	orbitRadius_ = 200;
	angle_ = 0;
	range_ = 70;
	dmg_ = 10;
	dmgGrowthRate_ = 5.f;
	owner_->AddComponent<Transform>();
	owner_->AddComponent<RigidBody>();
	owner_->AddComponent<Sprite>();
	owner->AddComponent<AnimationComp>();
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/boomerang.png", "Attack");
	owner->GetComponent<AnimationComp>()->ChangeAnimation("Attack");
	owner->GetComponent<Transform>()->SetScale({ range_, range_ });

	owner_->AddComponent<BoxCollider>();
	BoxCollider* col = owner_->GetComponent<BoxCollider>();
	col->SetLayer(Collider::P_ATTACK);
	col->SetType(Collider::AABB_TYPE);
	col->SetHandler(static_cast<EventEntity*>(this));
}

boomerang::~boomerang()
{
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Transform>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<RigidBody>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Sprite>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<AnimationComp>())));
	GameObjectManager::GetInstance().RemoveObject(owner_->GetName());
}

void boomerang::Update()
{
	float dt = AEFrameRateControllerGetFrameRate();
	if (mode == set)
	{
		lifetime = 30000;
		mode = go;
	}
	if (mode == go)
	{
		if (lifetime <= 0)
		{
			mode = set;
			owner_->active_ = false;
		}
		else
		{
			lifetime -= dt;
			owner_->GetComponent<Transform>()->SetRotation(
				owner_->GetComponent<Transform>()->GetRotation() + 0.01 * dt);
			AEVec2 playerPos = player_->GetComponent<Transform>()->GetPosition();

			angle_ += rotationSpeed_ * dt;
			if (angle_ >= 360.0f) 
				angle_ -= 360.0f; // 각도가 360도를 넘지 않도록 처리

			float offsetX = orbitRadius_ * cosf(AEDegToRad(angle_));
			float offsetY = orbitRadius_ * sinf(AEDegToRad(angle_));

			// 4. 오브젝트의 위치를 플레이어를 기준으로 설정
			AEVec2 newPos;
			newPos.x = playerPos.x + offsetX;
			newPos.y = playerPos.y + offsetY;
			owner_->GetComponent<Transform>()->SetPosition(newPos);
		}
	}
}

void boomerang::LevelUp()
{
	dmg_ += int(dmg_ * dmgGrowthRate_ / 100);
}

void boomerang::AttackObject()
{
}

ComponentSerializer* boomerang::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<boomerang>())
		std::cout << "boomerang::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<boomerang>();
}

void boomerang::OnEvent(BaseEvent*)
{
}

void boomerang::OnCollision(CollisionEvent* event)
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

void boomerang::LoadFromJson(const json&)
{
}

json boomerang::SaveToJson()
{
	return json();
}
