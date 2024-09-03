#pragma once
#include "SpawnManager.h"

class ItemManager : public SpawnManager
{
private:
	std::uniform_int_distribution<int> itemRate_{ 0, 99 };
	int magnetProb = 66;
	int healthProb = 100;

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

	void Initialize(int maxNum) override;

	void Spawn() override;
	void Release(GameObject* obj) override;

	void Clear() override;

	friend class GameObjectManager;
};