#include "Bullet.h"
#include "../../Utils/MathUtils.h"
#include "../../Manager/GameObjectManager.h"

BulletComp::BulletComp(GameObject* owner) : LogicComponent(owner)
{
	bulletSpeed = 10.f;
	bulletDmg	= 3.f;

	owner_->AddComponent<Transform>();
	boss = GameObjectManager::GetInstance().GetObjectA("boss");
	player = GameObjectManager::GetInstance().GetObjectA("TestObj");

	InitBullet();
}

void BulletComp::Update()
{
	RigidBody* bulletRigd = owner_->GetComponent<RigidBody>();

	bulletRigd->AddVelocity(unitDir * bulletSpeed);
}

void BulletComp::InitBullet()
{
	Transform* bulletTrans = owner_ ->GetComponent<Transform>();
	Transform* playerTrans = player ->GetComponent<Transform>();
	RigidBody* bulletRigd  = owner_ ->GetComponent<RigidBody>();

	bulletTrans->SetPosition(boss->GetComponent<Transform>()->GetPosition());

	AEVec2 dir = playerTrans->GetPosition() - bulletTrans->GetPosition();

	AEVec2Normalize(&unitDir, &dir);

	bulletRigd->AddVelocity(unitDir * bulletSpeed);
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
