#include "Bullet.h"

#include "../../Event/Event.h"
#include <iostream>
#include "../../Utils/MathUtils.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Component/AnimationComp.h"

BulletComp::BulletComp(GameObject* owner) : LogicComponent(owner)
{
	bulletSpeed_ = 100.f;
	bulletDmg_	 = 3.f;
	
	owner_->AddComponent<BoxCollider>();
	owner_->AddComponent<Sprite>();
	owner_->AddComponent<AnimationComp>();

	//owner_->GetComponent<Transform>()->SetScale({ 50, 50 });
	owner_->GetComponent<Transform>()->SetScale({ 500, 500 });

	BoxCollider* col = owner_->GetComponent<BoxCollider>();
	col->SetType(Collider::OBB_TYPE);
	col->SetLayer(Collider::E_ATTACK);
	col->SetHandler(static_cast<EventEntity*>(this));

	owner_->GetComponent<AnimationComp>()->AddAnimation("BossPhase1");

	for (int i = 0; i < 40; i++)
	{
		std::string anim = "Assets/boss1_Anime/Atk/phase1ATK/phase1_" + std::to_string(i) + ".png";

		owner_->GetComponent<AnimationComp>()->AddDetail(anim, "BossPhase1");
	}
	for (int i = 38; i >= 0; i--)
	{
		std::string anim = "Assets/boss1_Anime/Atk/phase1ATK/phase1_" + std::to_string(i) + ".png";

		owner_->GetComponent<AnimationComp>()->AddDetail(anim, "BossPhase1");
	}

	owner_->GetComponent<AnimationComp>()->SetTerm(50);

	//AddAnimation("BossPhase1");
	//AddAnimation("BossPhase2");
	//AddAnimation("BossPhase3");
	owner_->GetComponent<AnimationComp>()->ChangeAnimation("BossPhase1");

	boss   = GameObjectManager::GetInstance().GetObjectA("boss");
	player = GameObjectManager::GetInstance().GetObjectA("player");
}

void BulletComp::Update()
{	
	RigidBody* bulletRigd = owner_->GetComponent<RigidBody>();
	bulletRigd->AddVelocity(unitDir * bulletSpeed_);
}

void BulletComp::OnEvent(BaseEvent* event)
{
}

void BulletComp::OnCollision(CollisionEvent* event)
{
	Player* player = event->from_->GetComponent<Player>();
	if (check_ && player)
	{
		player->AddHp(-bulletDmg_);
		check_ = false;

		return;
	}
}

void BulletComp::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void BulletComp::FireBullet()
{
	Transform* bulletTrans = owner_ ->GetComponent<Transform>();
	RigidBody* bulletRigd  = owner_ ->GetComponent<RigidBody>();

	Transform* playerTrans = player ->GetComponent<Transform>();

	bulletTrans->SetPosition(boss->GetComponent<Transform>()->GetPosition());

	AEVec2 dir = playerTrans->GetPosition() - bulletTrans->GetPosition();

	AEVec2Normalize(&unitDir, &dir);

	bulletRigd->AddVelocity(unitDir * bulletSpeed_);
}

void BulletComp::BarrageBullet(bool _bool = false)
{
	returnBullet = _bool;

	Transform* bulletTrans = owner_->GetComponent<Transform>();
	RigidBody* bulletRigd = owner_->GetComponent<RigidBody>();

	bulletTrans->SetPosition(boss->GetComponent<Transform>()->GetPosition());

	bulletRigd->AddVelocity(unitDir * bulletSpeed_);
}


void BulletComp::LoadFromJson(const json&)
{
		
}

json BulletComp::SaveToJson()
{
	return json();
}

ComponentSerializer* BulletComp::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<BulletComp>())
		std::cout << "BulletComp::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<BulletComp>();
}
