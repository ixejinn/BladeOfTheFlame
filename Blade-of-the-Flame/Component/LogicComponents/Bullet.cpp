#include "Bullet.h"
#include "../../Utils/MathUtils.h"
#include "../../Manager/GameObjectManager.h"

BulletComp::BulletComp(GameObject* owner) : LogicComponent(owner)
{
	bulletSpeed_ = 100.f;
	bulletDmg_	 = 3.f;
	
	owner_->AddComponent<Transform>();
	owner_->AddComponent<RigidBody>();
	owner_->AddComponent<Sprite>();
	owner_->GetComponent<Transform>()->SetScale({ 50, 50 });
	owner_->GetComponent<Sprite>   ()->SetTexture("Assets/YeeHead.png");

	boss   = GameObjectManager::GetInstance().GetObjectA("boss");
	player = GameObjectManager::GetInstance().GetObjectA("TestObj");

}

void BulletComp::Update()
{	
	RigidBody* bulletRigd = owner_->GetComponent<RigidBody>();
	bulletRigd->AddVelocity(unitDir * bulletSpeed_);

	if (returnBullet)
	{
		time++;
		if (time == 40)
		{
			f32 a = -1;
			unitDir.x = unitDir.x * a;
			unitDir.y = unitDir.y * a;
			time = 0;
			returnBullet = false;
		}
	}
}

void BulletComp::RemoveFromManager()
{
	//TODO::
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

	//AEVec2 nonDir;
	/*AEVec2 result;
	AEVec2Add(&result,&unitDir,&nonDir);*/

	//AEVec2Normalize(&unitDir, &unitDir);

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
