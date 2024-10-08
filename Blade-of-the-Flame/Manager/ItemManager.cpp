#include "ItemManager.h"

#include "../Component/LogicComponents/Items/MagnetItem.h"
#include "../Component/LogicComponents/Items/HealthItem.h"

ItemManager::ItemManager() : healthSpawner_(), magnetSpawner_()
{
}

void ItemManager::Initialize(int maxNum, int maxActiveNum, double spawnPeriod, int spawnNumPerWave)
{
	healthSpawner_.Initialize(maxNum, maxActiveNum / 3, spawnPeriod * 3, spawnNumPerWave / 3);
	magnetSpawner_.Initialize(maxNum, maxActiveNum, spawnPeriod, spawnNumPerWave);
}

void ItemManager::Spawn()
{
	healthSpawner_.Spawn();
	magnetSpawner_.Spawn();
}

void ItemManager::Release(ItemType type, GameObject* obj)
{
	switch (type)
	{
	case HEALTH:
		healthSpawner_.Release(obj);
		break;

	case MAGNET:
		magnetSpawner_.Release(obj);
		break;
	}
}

void ItemManager::Clear()
{
	healthSpawner_.Clear();
	magnetSpawner_.Clear();
}
