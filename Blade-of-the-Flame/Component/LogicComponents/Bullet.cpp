#include "Bullet.h"
#include "../../Event/Event.h"
#include "../../Utils/MathUtils.h"
#include "../../Manager/GameObjectManager.h"

BulletComp::BulletComp(GameObject* owner) : LogicComponent(owner)
{
	bulletSpeed_ = 100.f;
	bulletDmg_	 = 3.f;
	
	owner_->AddComponent<BoxCollider>();
	owner_->AddComponent<Sprite>();

	owner_->GetComponent<Transform>()->SetScale({ 50, 50 });

	BoxCollider* col = owner_->GetComponent<BoxCollider>();
	col->SetType(Collider::OBB_TYPE);
	col->SetLayer(Collider::E_ATTACK);
	col->SetHandler(static_cast<EventEntity*>(this));

	owner_->GetComponent<Sprite>   ()->SetTexture("Assets/YeeHead.png");

	boss   = GameObjectManager::GetInstance().GetObjectA("boss");
	player = GameObjectManager::GetInstance().GetObjectA("player");

	timeStart_ = std::chrono::system_clock::now();
}

void BulletComp::Update()
{	
	RigidBody* bulletRigd = owner_->GetComponent<RigidBody>();
	bulletRigd->AddVelocity(unitDir * bulletSpeed_);

	//탄막 패턴 쐇다가 다시 돌아오는 기능
	//if (returnBullet)
	//{
	//	time++;
	//	if (time == 40)
	//	{
	//		f32 a = -1;
	//		unitDir.x = unitDir.x * a;
	//		unitDir.y = unitDir.y * a;
	//		time = 0;
	//		returnBullet = false;
	//	}
	//}
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
