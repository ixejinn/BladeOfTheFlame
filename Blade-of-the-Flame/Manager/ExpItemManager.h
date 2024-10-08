#pragma once
#include "Spawner.h"

class ExpItem;

class ExpItemManager
{
private:
	Spawner<ExpItem> expSpawner_;

	ExpItemManager();
	~ExpItemManager() = default;

	ExpItemManager(const ExpItemManager&) = delete;
	ExpItemManager& operator =(const ExpItemManager&) = delete;
	ExpItemManager(ExpItemManager&&) = delete;
	ExpItemManager& operator =(ExpItemManager&&) = delete;

public:
	static ExpItemManager& GetInstance()
	{
		static ExpItemManager instance;
		return instance;
	}

	void Initialize(int maxNum);

	ExpItem* Spawn(const AEVec2& pos);
	void Release(GameObject* obj);

	void Clear();
};