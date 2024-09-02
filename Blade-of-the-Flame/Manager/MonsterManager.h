#pragma once
#include "SpawnManager.h"

class MonsterManager : public SpawnManager
{
private:
	MonsterManager();
	~MonsterManager() = default;

	MonsterManager(const MonsterManager&) = delete;
	MonsterManager& operator =(const MonsterManager&) = delete;
	MonsterManager(MonsterManager&&) = delete;
	MonsterManager& operator =(MonsterManager&&) = delete;

public:
	static MonsterManager& GetInstance()
	{
		static MonsterManager instance;
		return instance;
	}

	void Initialize(int maxNum) override;

	void Spawn() override;
	void Release(GameObject* obj) override;

	void Clear() override;

	friend class GameObjectManager;
};