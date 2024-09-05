#include "BossComp.h"
#include "../../Manager/GameObjectManager.h"

BossComp::BossComp(GameObject* owner) : LogicComponent(owner)
{
	player = GameObjectManager::GetInstance().GetObjectA("TestObj");
	boss = GameObjectManager::GetInstance().GetObjectA("boss");
}

GameObject* BossComp::CreateBulletObj()
{
	std::string unique_bullet_name = "bullet" + std::to_string(bullet.size());
	GameObject* addBullet = GameObjectManager::GetInstance().CreateObject(unique_bullet_name);

	bullet.push_back(addBullet);
	addBullet->AddComponent<BulletComp>();

	return addBullet;
}

void BossComp::Update()
{

}

void BossComp::RemoveFromManager()
{
	//TODO::
}

ComponentSerializer* BossComp::CreateComponent(GameObject* owner)
{
	return nullptr;
}
