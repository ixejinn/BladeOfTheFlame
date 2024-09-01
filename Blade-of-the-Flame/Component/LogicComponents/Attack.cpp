#include "Attack.h"

#include "../../Manager/GameObjectManager.h"

Attack::Attack(GameObject* owner) : LogicComponent(owner)
{
	owner_->active_ = false;

	player_ = GameObjectManager::GetInstance().GetObjectA("player");

}