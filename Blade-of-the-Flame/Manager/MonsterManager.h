#pragma once
#include <stack>
#include <chrono>
#include "GameObjectManager.h"
#include "../Utils/RandomEngine.h"
#include "../Utils/Utils.h"

class MonsterManager
{
private:
	std::stack<GameObject*> pool_;

	int maxNum_ = 0;
	int activeNum_ = 0;
	int maxActiveNum_ = 100;

	std::uniform_int_distribution<int> spawnZone_{ 0, 3 };
	std::uniform_int_distribution<int> spawnX_{ -windowWidth / 2, windowWidth / 2 };
	std::uniform_int_distribution<int> spawnY_{ -windowHeight / 2, windowHeight / 2 };
	int spawnOffset_ = 50;

	std::chrono::system_clock::time_point timeStart_;
	double spawnPeriod_ = 2.0;
	int spawnNumPerWave = 5;

	MonsterManager() = default;
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

	void Initialize(int maxNum);

	void SpawnMonster();
	void Release(GameObject* obj);

	void Clear();

	friend class GameObjectManager;
};