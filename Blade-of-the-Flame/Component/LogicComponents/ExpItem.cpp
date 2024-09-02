#include "ExpItem.h"

#include "../../Event/Event.h"
#include "../../Manager/GameObjectManager.h"

ExpItem::ExpItem(GameObject* owner) : BaseItem(owner)
{
	owner_->GetComponent<BoxCollider>()->SetLayer(Collider::EXP_ITEM);
	owner_->GetComponent<Sprite>()->SetColor({ 0, 255, 0 });

	trans_ = owner_->GetComponent<Transform>();
	playerTrans_ = GameObjectManager::GetInstance().GetObjectA("player")->GetComponent<Transform>();
	rb_ = owner_->GetComponent<RigidBody>();
}

void ExpItem::Update()
{
	AEVec2 playerPos = playerTrans_->GetPosition();
	AEVec2 pos = trans_->GetPosition();
	AEVec2 dir = playerPos - pos;
	f32 squareDist = AEVec2SquareLength(&dir);

	/*if (squareDist > 9 * windowHeight * windowHeight)
		manager_.Release(owner_);*/
}

void ExpItem::LoadFromJson(const json&)
{
}

json ExpItem::SaveToJson()
{
	return json();
}

void ExpItem::OnEvent(BaseEvent* event)
{
}

void ExpItem::OnCollision(CollisionEvent* event)
{
	Player* player = event->from_->GetComponent<Player>();
	if (player)
	{
		switch (event->fromType_)
		{
		case Collider::CIRCLE_TYPE:
		{
			AEVec2 playerPos = playerTrans_->GetPosition();
			AEVec2 pos = trans_->GetPosition();
			AEVec2 moveDir = playerPos - pos, unitMoveDir;
			AEVec2Normalize(&unitMoveDir, &moveDir);
			rb_->AddVelocity(unitMoveDir * attractionSpeed_);

			break;
		}

		case Collider::AABB_TYPE:
		{
			owner_->active_ = false;

			break;
		}
		}
	}
}

ComponentSerializer* ExpItem::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<ExpItem>())
		std::cout << "ExpItem::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<ExpItem>();
}
