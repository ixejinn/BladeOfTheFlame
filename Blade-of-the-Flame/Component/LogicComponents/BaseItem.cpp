#include "BaseItem.h"

#include "../../GameObject/GameObject.h"

BaseItem::BaseItem(GameObject* owner) : LogicComponent(owner)
{
	owner_->active_ = false;
}

void BaseItem::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}
