#include "ExpItemManager.h"
#include "../Component/LogicComponents/Items/ExpItem.h"

void ExpItemManager::Initialize(int maxNum)
{
	if (!pool_.empty())
		Clear();
	maxNum_ = maxNum;
	maxActiveNum_ = maxNum;

	GameObjectManager& gom = GameObjectManager::GetInstance();
	for (int i = 0; i < maxNum; i++)
	{
		GameObject* obj = gom.CreateObject("expItem" + std::to_string(i));
		obj->AddComponent<ExpItem>();
		obj->GetComponent<ExpItem>()->SetUse(false);
		obj->active_ = false;
		pool_.push(obj);
	}
}

ExpItem* ExpItemManager::Spawn(const AEVec2& pos)
{
	if (pool_.empty())
	{
		std::cout << "ExpItemManager::Spawn() Empty pool" << std::endl;
		return nullptr;
	}

	GameObject* item = pool_.top();
	pool_.pop();
	activeNum_++;

	item->GetComponent<Transform>()->SetPosition(pos);
	item->GetComponent<RigidBody>()->ClearVelocity();
	item->active_ = true;

	item->GetComponent<BoxCollider>()->Update();

	return item->GetComponent<ExpItem>();
}

void ExpItemManager::Release(GameObject* obj)
{
	pool_.push(obj);
	activeNum_--;
}

void ExpItemManager::Clear()
{
	while (!pool_.empty())
		pool_.pop();
}
