#include "bubble.h"
#include <iostream>
#include "../../../Event/Event.h"
#include "../../../Manager/EventManager.h"
#include "../Monster.h"

bubble::bubble(GameObject* owner) : BaseAttack(owner)
{
	mode = set;
	dmgGrowthRate_ = 10.f;
	dmg_ = 20;
	tempdmg = dmg_;
	range_ = 100;
	owner->AddComponent<Transform>();
	owner->AddComponent<RigidBody>();
	owner->AddComponent<Sprite>();
	owner->AddComponent<AnimationComp>();

	owner->GetComponent<AnimationComp>()->AddAnimation("1");
	owner->GetComponent<AnimationComp>()->AddAnimation("2");
	owner->GetComponent<AnimationComp>()->AddAnimation("3");

	owner->GetComponent<AnimationComp>()->AddDetail("Assets/bubbleAnime/0.png", "1");

	owner->GetComponent<AnimationComp>()->AddDetail("Assets/bubbleAnime/1.png", "2");

	owner->GetComponent<AnimationComp>()->AddDetail("Assets/bubbleAnime/2.png", "3");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/bubbleAnime/3.png", "3");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/bubbleAnime/4.png", "3");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/bubbleAnime/5.png", "3");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/bubbleAnime/6.png", "3");

	owner->GetComponent<AnimationComp>()->SetTerm(200);
	owner->GetComponent<AnimationComp>()->ChangeAnimation("1");

	owner->GetComponent<Transform>()->SetScale({ 0, 0 });

	owner_->AddComponent<CircleCollider>();
	CircleCollider* col = owner_->GetComponent<CircleCollider>();
	col->SetLayer(Collider::P_ATTACK);
	col->SetType(Collider::CIRCLE_TYPE);
	col->SetHandler(static_cast<EventEntity*>(this));
}

bubble::~bubble()
{
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Transform>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<RigidBody>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Sprite>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<AnimationComp>())));
	GameObjectManager::GetInstance().RemoveObject(owner_->GetName());
}

void bubble::Update()
{
	if (mode == set)
	{
		dmg_ = 0;
		lifetime = 40000;
		owner_->GetComponent<Transform>()->SetScale({ 0, 0 });
		owner_->GetComponent<AnimationComp>()->ChangeAnimation("1");
		owner_->GetComponent<RigidBody>()->ClearVelocity();
		owner_->GetComponent<Transform>()->SetPosition(player_->GetComponent<Transform>()->GetPosition());
		AEInputInit();
		s32 x, y;
		AEInputGetCursorPosition(&x, &y);
		AEVec2 mousePosF({ static_cast<float>(x), static_cast<float>(y) });
		if (!AEInputCheckCurr(AEVK_RBUTTON))
		{
			AEVec2 attackDir{ convert(mousePosF) - owner_->GetComponent<Transform>()->GetPosition() };
			AEVec2Normalize(&dir, &attackDir);
			mode = fire;
			dmg_ = tempdmg;
			owner_->GetComponent<RigidBody>()->AddVelocity(dir * 1000);
			owner_->GetComponent<Transform>()->SetScale({ range_, range_ });
			player_->GetComponent<Player>()->SkillGage = 0;
		}
	}
	if (mode == fire)
	{
		if (lifetime > 0)
		{
			float dt = AEFrameRateControllerGetFrameRate();
			lifetime -= dt;

			owner_->GetComponent<RigidBody>()->AddVelocity(owner_->GetComponent<RigidBody>()->GetVelocity()/10.8);

			if (lifetime <= 2000)
			{
				if (lifetime <= 1000)
				{
					owner_->GetComponent<AnimationComp>()->ChangeAnimation("3");
				}
				else
					owner_->GetComponent<AnimationComp>()->ChangeAnimation("2");
			}
			
			// 현재 위치와 속도 가져오기
			AEVec2 position = owner_->GetComponent<Transform>()->GetPosition();
			AEVec2 playerPos = player_->GetComponent<Transform>()->GetPosition();
			AEVec2 velocity = owner_->GetComponent<RigidBody>()->GetVelocity();

			// 벽 충돌 감지 (왼쪽 위가 (0, 0)인 경우)
			if (position.x < playerPos.x - windowWidth / 2 || position.x > playerPos.x + windowWidth / 2 ||
				position.y < playerPos.y - windowHeight / 2 || position.y > playerPos.y + windowHeight / 2)
			{
				// 벽에 닿으면 반사
				if (position.x < playerPos.x - windowWidth / 2 || position.x > playerPos.x + windowWidth / 2)
					velocity.x *= -1; // X축 반사
				if (position.y < playerPos.y - windowHeight / 2 || position.y > playerPos.y + windowHeight / 2)
					velocity.y *= -1; // Y축 반사;

				// 반사된 속도를 다시 설정
				owner_->GetComponent<RigidBody>()->SetVelocity(velocity);
			}
		}
		else
		{
			mode = set;
			owner_->active_ = false;
		}
	}
}

void bubble::LevelUp()
{
	tempdmg += int(tempdmg * dmgGrowthRate_ / 100);
}

void bubble::AttackObject()
{
}

void bubble::LoadFromJson(const json&)
{
}

json bubble::SaveToJson()
{
	return json();
}

ComponentSerializer* bubble::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<bubble>())
		std::cout << "bubble::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<bubble>();
}

void bubble::OnEvent(BaseEvent*)
{
}

void bubble::OnCollision(CollisionEvent* event)
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
