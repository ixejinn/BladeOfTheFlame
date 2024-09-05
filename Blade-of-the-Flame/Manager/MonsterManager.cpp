#include "MonsterManager.h"

#include <string>
#include <typeindex>
#include "../Event/Event.h"
#include "../Manager/EventManager.h"

MonsterManager::MonsterManager() : SpawnManager()
{
	spawnPeriod_ = 5.0;
	spawnNumPerWave_ = 5;

	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(LevelUpEvent)), static_cast<EventEntity*>(this));
	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(SpawnBossEvent)), static_cast<EventEntity*>(this));
}

void MonsterManager::Initialize(int maxNum)
{
	if (!pool_.empty())
		Clear();
	maxNum_ = maxNum;
	maxActiveNum_ = maxNum;

	GameObjectManager& gom = GameObjectManager::GetInstance();
	for (int i = 0; i < maxNum; i++)
	{
		GameObject* obj = gom.CreateObject("monster" + std::to_string(i));
		obj->AddComponent<Monster>();
		obj->GetComponent<Transform>()->SetPosition(0.1f, 0.1f);
		obj->active_ = false;
		pool_.push(obj);
	}

	timeStart_ = std::chrono::system_clock::now();
}

void MonsterManager::Spawn()
{
	if (activeNum_ >= maxActiveNum_)
		return;

	std::chrono::duration<double> dt = std::chrono::system_clock::now() - timeStart_;
	if (dt.count() < spawnPeriod_)
		return;

	timeStart_ = std::chrono::system_clock::now();
	static Transform* playerTrans = GameObjectManager::GetInstance().GetObjectA("player")->GetComponent<Transform>();
	static auto& engine = RandomEngine::GetInstance().GetEngine();

	for (int i = 0; i < spawnNumPerWave_; i++)
	{
		if (pool_.empty())
			return;

		GameObject* monster = pool_.top();
		pool_.pop();
		activeNum_++;

		int zone = spawnZone_(engine);
		int x = 0, y = 0;
		int halfWidth = windowWidth / 2, halfHeight = windowHeight / 2;

		switch (zone)
		{
		case 0:	// Up side
			x = spawnX_(engine);
			y = halfHeight + spawnOffset_ + x / 100;
			break;

		case 1:	// Right side
			y = spawnY_(engine);
			x = halfWidth + spawnOffset_ + y / 100;
			break;

		case 2:	// Down side
			x = spawnX_(engine);
			y = -halfHeight - spawnOffset_ - x / 100;
			break;

		case 3:	// Left side
			y = spawnY_(engine);
			x = -halfWidth - spawnOffset_ - y / 100;
			break;
		}

		AEVec2 playerPos = playerTrans->GetPosition();
		x += int(playerPos.x);
		y += int(playerPos.y);

		monster->GetComponent<Transform>()->SetPosition(float(x), float(y));
		monster->active_ = true;
	}
}

void MonsterManager::Release(GameObject* obj)
{
	obj->GetComponent<RigidBody>()->ClearVelocity();
	obj->active_ = false;
	pool_.push(obj);
	activeNum_--;
}

void MonsterManager::Clear()
{
	while (!pool_.empty())
		pool_.pop();
}

void MonsterManager::OnEvent(BaseEvent* event)
{
	if (dynamic_cast<LevelUpEvent*>(event))
	{
		LevelUpEvent* lvlUp = static_cast<LevelUpEvent*>(event);
		maxActiveNum_ = maxActiveNum_ * lvlUp->level;
	}
	else if (dynamic_cast<SpawnBossEvent*>(event))
	{
		maxActiveNum_ = 3;
	}
}

void MonsterManager::OnCollision(CollisionEvent*)
{
}
