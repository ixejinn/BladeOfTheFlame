#include "ExpItemManager.h"
#include "../Component/LogicComponents/Items/ExpItem.h"

ExpItemManager::ExpItemManager() : expSpawner_() {}

void ExpItemManager::Initialize(int maxNum)
{
	expSpawner_.Initialize(maxNum, maxNum, 0.0, 0);
}

ExpItem* ExpItemManager::Spawn(const AEVec2& pos)
{
	return expSpawner_.Spawn(pos);
}

void ExpItemManager::Release(GameObject* obj)
{
	expSpawner_.Release(obj);
}

void ExpItemManager::Clear()
{
	expSpawner_.Clear();
}
