#pragma once
#include <stack>
#include "GameObjectManager.h"

class ExpItemManager
{
private:
	std::stack<GameObject*> pool_;

	int maxNum_ = 0;
	int activeNum_ = 0;
	int maxActiveNum_ = 0;

	ExpItemManager() = default;
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