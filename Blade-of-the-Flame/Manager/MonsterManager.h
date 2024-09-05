#pragma once
#include "SpawnManager.h"
#include "../Event/EventEntity.h"

class MonsterManager : public SpawnManager, public EventEntity
{
private:
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

	void Initialize(int maxNum) override;

	void Spawn() override;
	void Release(GameObject* obj) override;

	void AddCapturedCount() { capturedCount_++; }

	void Clear() override;

	const int& GetCapturedCount() const { return capturedCount_; }

	void OnEvent(BaseEvent*) override;
	void OnCollision(CollisionEvent*) override;

	friend class GameObjectManager;
};