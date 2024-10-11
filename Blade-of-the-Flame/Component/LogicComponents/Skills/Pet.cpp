#include "Pet.h"

#include "petBullet.h"
#include "../../../Event/Event.h"
#include "../Monster.h"
#include "../../../Utils/Utils.h"
#include <iostream>

Pet::Pet(GameObject* owner) : BaseAttack(owner)
{
	count = 0;
	cState = ready;
	lifetime = 30000;
	range_ = 100;
	dmg_ = 2;
	dmgGrowthRate_ = 5.f;
	owner_->AddComponent<Transform>();
	owner_->AddComponent<RigidBody>();
	owner_->AddComponent<Sprite>();
	owner->AddComponent<AnimationComp>();
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/pet.png", "Attack");
	owner->GetComponent<AnimationComp>()->ChangeAnimation("Attack");

	owner_->AddComponent<CircleCollider>();
	CircleCollider* col = owner_->GetComponent<CircleCollider>();
	col->SetLayer(Collider::SEARCH);
	col->SetType(Collider::CIRCLE_TYPE);
	col->SetHandler(static_cast<EventEntity*>(this));
	col->SetRadius(500);

	for(int i = 0;i<13;i++)
	{
		GameObject* p = GameObjectManager::GetInstance().CreateObject(std::to_string(i));
		p->AddComponent<PB>();
		p->GetComponent<PB>()->SetPlayer(player_);
		pbs.push_back(p);
	}
}

Pet::~Pet() 
{
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Transform>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<RigidBody>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Sprite>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<AnimationComp>())));
	GameObjectManager::GetInstance().RemoveObject(owner_->GetName());
}

void Pet::Update()
{
	float dt = AEFrameRateControllerGetFrameRate();

	if (cState == ready)
	{
		fire = false;
		summon = 0;
		lifetime = 30000;
		owner_->GetComponent<Transform>()->SetScale({ 0, 0 });

		if (!AEInputCheckCurr(AEVK_LBUTTON))
		{
			owner_->GetComponent<Transform>()->SetScale({ range_, range_ });
			cState = shoot;
		}
	}
	else if (cState == shoot)
	{
		if (lifetime > 0)
		{
			lifetime -= dt;
			summon += dt;

			// 플레이어의 위치를 정확히 참조
			AEVec2 playerPos = player_->GetComponent<Transform>()->GetPosition();

			// 좌측 발사체: 플레이어의 위치에서 일정한 간격만큼 왼쪽에 생성되도록 설정
			float offsetDistance = 100.f;  // 좌우 간격
			AEVec2 perpOffset{ -dir.y, dir.x };  // 수직 벡터 방향으로 좌측 설정
			AEVec2 leftFlamePos = playerPos + (perpOffset * offsetDistance);

			// 왼쪽 발사체의 위치 설정
			owner_->GetComponent<Transform>()->SetPosition(leftFlamePos);

			// 마우스 위치를 가져와 월드 좌표로 변환
			s32 x, y;
			AEInputGetCursorPosition(&x, &y);
			AEVec2 mousePosF({ static_cast<float>(x), static_cast<float>(y) });
			AEVec2 worldMousePos = convert(mousePosF);

			if (summon >= 1000)
			{
				fire = true;
			}
	}
		else
		{
			cState = ready;
			owner_->active_ = false;
		}
	}
}

void Pet::LevelUp()
{
	dmg_ += int(dmg_ * dmgGrowthRate_ / 100);
}

void Pet::AttackObject()
{
}

ComponentSerializer* Pet::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Pet>())
		std::cout << "Pet::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Pet>();
}

void Pet::OnEvent(BaseEvent*)
{
}

void Pet::OnCollision(CollisionEvent* event)
{
	BaseMonster* monster = event->monster;
	if (monster && fire == true)
	{
		AEVec2 monsterPos = monster->GetOwner()->GetComponent<Transform>()->GetPosition();
		if (count >= 13)
			count = 0;
		pbs[count]->GetComponent<Transform>()->SetPosition(owner_->GetComponent<Transform>()->GetPosition());
		pbs[count]->GetComponent<PB>()->goalPos = monsterPos;
		pbs[count]->active_ = true;
		fire = false;
		summon = 0;
		count++;
	}

	Boss1* boss = event->from_->GetComponent<Boss1>();
	if (boss && fire == true)
	{
		AEVec2 bossPos = boss->GetOwner()->GetComponent<Transform>()->GetPosition();
		if (count >= 13)
			count = 0;
		pbs[count]->GetComponent<Transform>()->SetPosition(owner_->GetComponent<Transform>()->GetPosition());
		pbs[count]->GetComponent<PB>()->goalPos = bossPos;
		pbs[count]->active_ = true;
		fire = false;
		summon = 0;
		count++;
	}
}

void Pet::LoadFromJson(const json&)
{
}

json Pet::SaveToJson()
{
	return json();
}
