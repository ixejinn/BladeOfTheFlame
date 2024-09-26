#include "BaseAttack.h"

#include "../../Manager/GameObjectManager.h"

BaseAttack::BaseAttack(GameObject* owner) : LogicComponent(owner)
{
	owner_->active_ = false;

	player_ = GameObjectManager::GetInstance().GetObjectA("player");

	owner_->attackPtr_ = this;
}

void BaseAttack::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}
