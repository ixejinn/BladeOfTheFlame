#pragma once
#include "Spawner.h"
#include "SpawnManager.h"
#include "../Component/LogicComponents/Monsters/NormalMonster.h"
#include "../Component/LogicComponents/Monsters/InstakillMonster.h"
#include "../Event/EventEntity.h"

class MonsterManager : public SpawnManager, public EventEntity
{
public:
	enum MonsterType
	{
		NORMAL,
		INSTAKILL
	};

private:
	Spawner<NormalMonster> normalSpawner_;
	Spawner<InstakillMonster> instakillSpawner_;

	int capturedCount_ = 0;

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

	void Initialize(int maxNum, int maxActiveNum, double spawnPeriod, int spawnNumPerWave) override;

	void Spawn() override;
	void Release(MonsterType type, GameObject* obj);

	void AddCapturedCount() { capturedCount_++; }

	void Clear() override;

	const int& GetCapturedCount() const { return capturedCount_; }

	void OnEvent(BaseEvent*) override;
	void OnCollision(CollisionEvent*) override;

	friend class GameObjectManager;
};