#include "MonsterManager.h"

#include <string>

void MonsterManager::Initialize(int maxNum)
{
	if (!pool_.empty())
		Clear();
	maxNum_ = maxNum;

	GameObjectManager& gom = GameObjectManager::GetInstance();
	for (int i = 0; i < maxNum; i++)
	{
		GameObject* obj = gom.CreateObject("monster" + std::to_string(i));
		obj->AddComponent<Monster>();
		obj->GetComponent<Transform>()->SetPosition(0.1, 0.1);
		obj->active_ = false;
		pool_.push(obj);
	}

	timeStart_ = std::chrono::system_clock::now();
}

void MonsterManager::SpawnMonster()
{
	if (activeNum_ >= maxActiveNum_)
		return;

	std::chrono::duration<double> dt = std::chrono::system_clock::now() - timeStart_;
	if (dt.count() < spawnPeriod_)
		return;

	timeStart_ = std::chrono::system_clock::now();
	static Transform* playerTrans = GameObjectManager::GetInstance().GetObjectA("player")->GetComponent<Transform>();
	static auto& engine = RandomEngine::GetInstance().GetEngine();

	for (int i = 0; i < spawnNumPerWave; i++)
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
		x += playerPos.x;
		y += playerPos.y;

		std::cout << zone << " " << x << ", " << y << std::endl;

		monster->GetComponent<Transform>()->SetPosition(x, y);
		monster->active_ = true;
	}
}

void MonsterManager::Release(GameObject* obj)
{
	pool_.push(obj);
	activeNum_--;
}

void MonsterManager::Clear()
{
}
