#pragma once
#include <stack>
#include <chrono>
#include "GameObjectManager.h"
#include "../Utils/RandomEngine.h"
#include "../Utils/Utils.h"

class SpawnManager
{
protected:
	std::stack<GameObject*> pool_;

	int maxNum_ = 0;
	int activeNum_ = 0;
	int maxActiveNum_ = 0;

	std::uniform_int_distribution<int> spawnZone_{ 0, 3 };
	std::uniform_int_distribution<int> spawnX_{ -windowWidth / 2, windowWidth / 2 };
	std::uniform_int_distribution<int> spawnY_{ -windowHeight / 2, windowHeight / 2 };
	int spawnOffset_ = 50;

	std::chrono::system_clock::time_point timeStart_;
	double spawnPeriod_ = 0.0;
	int spawnNumPerWave_ = 0;

	SpawnManager();
	virtual ~SpawnManager() = default;

public:
	virtual void Initialize(int maxNum) = 0;

	virtual void Spawn() = 0;
	virtual void Release(GameObject* obj) = 0;

	virtual void Clear() = 0;

	void SetMaxActiveNum(int num) { maxActiveNum_ = num; }

	//friend class GameObjectManager;
};