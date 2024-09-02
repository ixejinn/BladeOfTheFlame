#include "BaseAttack.h"

#include "../../Manager/GameObjectManager.h"

BaseAttack::BaseAttack(GameObject* owner) : LogicComponent(owner)
{
	owner_->active_ = false;

	player_ = GameObjectManager::GetInstance().GetObjectA("player");

}

void BaseAttack::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}
