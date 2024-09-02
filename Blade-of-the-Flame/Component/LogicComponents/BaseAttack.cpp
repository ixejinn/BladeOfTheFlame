#include "BaseAttack.h"

#include "../../Manager/GameObjectManager.h"

BaseAttack::BaseAttack(GameObject* owner) : LogicComponent(owner)
{
	owner_->active_ = false;

	player_ = GameObjectManager::GetInstance().GetObjectA("player");

}