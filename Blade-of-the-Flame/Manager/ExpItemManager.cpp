#include "ExpItemManager.h"
#include "../Component/LogicComponents/ExpItem.h"

void ExpItemManager::Initialize(int maxNum)
{
	if (!pool_.empty())
		Clear();
	maxNum_ = maxNum;

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

void ExpItemManager::Spawn(const AEVec2& pos)
{

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
