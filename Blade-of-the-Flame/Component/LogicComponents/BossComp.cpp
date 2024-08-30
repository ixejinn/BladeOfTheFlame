#include "BossComp.h"

#include "../../Manager/GameObjectManager.h"

BossComp::BossComp(GameObject* owner) : LogicComponent(owner)
{
	player = GameObjectManager::GetInstance().GetObjectA("TestObj");
}

void BossComp::Update()
{

}
