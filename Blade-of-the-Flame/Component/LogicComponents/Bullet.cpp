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
	owner_->GetComponent<RigidBody>()->AddVelocity(unitDir * bulletSpeed);
}

void BulletComp::LoadFromJson(const json&)
{
}

json BulletComp::SaveToJson()
{
	return json();
}

void BulletComp::InitBullet()
{
	owner_->GetComponent<Transform>()->SetPosition(boss->GetComponent<Transform>()->GetPosition());

	AEVec2 dir = player->GetComponent<Transform>()->GetPosition() - owner_->GetComponent<Transform>()->GetPosition();
	
	AEVec2Normalize(&unitDir, &dir);

	RigidBody* bulletRigd = owner_->GetComponent<RigidBody>();
	bulletRigd->AddVelocity(unitDir * bulletSpeed);
}

ComponentSerializer* BulletComp::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<BulletComp>())
		std::cout << "BulletComp::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<BulletComp>();
}
