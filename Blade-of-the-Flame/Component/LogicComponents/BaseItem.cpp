#include "BaseItem.h"

#include "../../GameObject/GameObject.h"

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
