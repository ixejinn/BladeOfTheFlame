#include <iostream>

#include "Bullet.h"
#include "../../Event/Event.h"
#include "../../Utils/MathUtils.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Component/AnimationComp.h"

BulletComp::BulletComp(GameObject* owner) : LogicComponent(owner), unitDir()
{
	bulletSpeed_ = 100.f;
	bulletDmg_	 = 0.f;
	time = 0.f;
	owner_->AddComponent<BoxCollider>();
	owner_->AddComponent<AnimationComp>();
	owner_->AddComponent<Sprite>();

	BoxCollider* col = owner_->GetComponent<BoxCollider>();

	col->SetType(Collider::OBB_TYPE);
	col->SetLayer(Collider::E_ATTACK);
	col->SetHandler(static_cast<EventEntity*>(this));

	owner_->AddComponent<AnimationComp>();
	owner_->GetComponent<AnimationComp>()->AddAnimation("BossPhase1");

	owner_->AddComponent<Sprite>();
	owner_->GetComponent<Transform>()->SetScale({ 200, 200 });
	
	for (int i = 0; i < 19; i++)
	{
		std::string anim = "Assets/boss1_Anime/Atk/phase2ATK/phase1_" + std::to_string(i) + ".png";
	
		owner_->GetComponent<AnimationComp>()->AddDetail(anim, "BossPhase1");
	}
	for (int i = 18; i >= 0; i--)
	{
		std::string anim = "Assets/boss1_Anime/Atk/phase2ATK/phase1_" + std::to_string(i) + ".png";
	
		owner_->GetComponent<AnimationComp>()->AddDetail(anim, "BossPhase1");
	}
	owner_->GetComponent<AnimationComp>()->SetTerm(50);

	owner_->GetComponent<AnimationComp>()->ChangeAnimation("BossPhase1");

	player = GameObjectManager::GetInstance().GetObjectA("player");

	col->SetScale({ 0.4f, 0.4f });
	col->SetCenter({ 0.f, -0.2f });
}

void BulletComp::Update()
{	
	time += 0.1f;

	CurveBullet();
	/*else
	{
		RigidBody* bulletRigd = owner_->GetComponent<RigidBody>();
		bulletRigd->AddVelocity(unitDir * bulletSpeed_);
	}*/
}

void BulletComp::OnEvent(BaseEvent* event)
{
}

void BulletComp::OnCollision(CollisionEvent* event)
{
	Player* player = event->from_->GetComponent<Player>();
	if (check_ && player)
	{
		player->AddHp(int(-bulletDmg_));
		check_ = false;
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

	//bulletTrans->SetPosition(boss->GetComponent<Transform>()->GetPosition());

	AEVec2 dir = playerTrans->GetPosition() - bulletTrans->GetPosition();

	AEVec2Normalize(&unitDir, &dir);

	bulletRigd->AddVelocity(unitDir * bulletSpeed_);
}

void BulletComp::BarrageBullet(bool _bool = false)
{
	returnBullet = _bool;

	Transform* bulletTrans = owner_->GetComponent<Transform>();
	RigidBody* bulletRigd = owner_->GetComponent<RigidBody>();

	//bulletTrans->SetPosition(boss->GetComponent<Transform>()->GetPosition());

	bulletRigd->AddVelocity(unitDir * bulletSpeed_);
}

void BulletComp::DownBullet()
{

}

void BulletComp::CurveBullet()
{
	Transform* bulletTrans = owner_->GetComponent<Transform>();

	AEVec2 currentBulletPos;

	float radian = ((time * PI / 180) * 100);

	currentBulletPos.x = time;
	currentBulletPos.y = sin(radian);

	unitDir = currentBulletPos;

	bulletTrans->SetPosition(unitDir);
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
