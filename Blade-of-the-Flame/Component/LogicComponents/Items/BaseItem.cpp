#include "BaseItem.h"

#include "../../../Event/Event.h"
#include "ExpItem.h"
#include "../../../GameObject/GameObject.h"

bool BaseItem::DeactiveIfFar()
{
	AEVec2 playerPos = playerTrans_->GetPosition();
	AEVec2 pos = trans_->GetPosition();
	AEVec2 dir = playerPos - pos;
	f32 squareDist = AEVec2SquareLength(&dir);

	if (squareDist > 9 * windowHeight * windowHeight)
		return true;
	return false;
}

BaseItem::BaseItem(GameObject* owner) : LogicComponent(owner), timeStart_()
{
	owner_->active_ = false;

	owner_->AddComponent<BoxCollider>();
	owner_->AddComponent<Sprite>();

	owner_->GetComponent<BoxCollider>()->SetHandler(static_cast<EventEntity*>(this));
}

void BaseItem::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void BaseItem::OnCollision(CollisionEvent* event)
{
	Player* player = event->from_->GetComponent<Player>();
	if (player)
		use_ = true;
}
