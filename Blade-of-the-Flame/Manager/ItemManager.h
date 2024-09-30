#pragma once
#include "Spawner.h"
#include "SpawnManager.h"

class HealthItem;
class MagnetItem;

class ItemManager : public SpawnManager
{
public:
	enum ItemType
	{
		HEALTH,
		MAGNET
	};

private:
	Spawner<HealthItem> healthSpawner_;
	Spawner<MagnetItem> magnetSpawner_;

	ItemManager();
	~ItemManager() = default;

	ItemManager(const ItemManager&) = delete;
	ItemManager& operator =(const ItemManager&) = delete;
	ItemManager(ItemManager&&) = delete;
	ItemManager& operator =(ItemManager&&) = delete;

public:
	static ItemManager& GetInstance()
	{
		static ItemManager instance;
		return instance;
	}

	void Initialize(int maxNum, int maxActiveNum, double spawnPeriod, int spawnNumPerWave) override;

	void Spawn() override;
	void Release(ItemType type, GameObject* obj);

	void Clear() override;

	friend class GameObjectManager;
};