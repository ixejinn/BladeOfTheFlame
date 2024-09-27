#include "ItemManager.h"

#include "../Component/LogicComponents/Items/MagnetItem.h"
#include "../Component/LogicComponents/Items/HealthItem.h"

ItemManager::ItemManager() : SpawnManager()
{
	spawnPeriod_ = 20.0;
	spawnNumPerWave_ = 3;
}

void ItemManager::Initialize(int maxNum)
{
	static auto& engine = RandomEngine::GetInstance().GetEngine();

	if (!pool_.empty())
		Clear();
	maxNum_ = maxNum;
	maxActiveNum_ = maxNum;

	int magnetNum = 0;
	int healthNum = 0;

	GameObjectManager& gom = GameObjectManager::GetInstance();
	for (int i = 0; i < maxNum; i++)
	{
		GameObject* obj = gom.CreateObject("item" + std::to_string(i));
		obj->active_ = false;

		if (magnetNum < magnetRate)
		{
			obj->AddComponent<MagnetItem>();
			magnetNum++;
		}
		else if (healthNum < healthRate)
		{
			obj->AddComponent<HealthItem>();
			healthNum++;

			if (healthNum == healthRate)
			{
				magnetNum = 0;
				healthNum = 0;
			}
		}
		else
			std::cerr << "[ERROR] ItemManager::Initialize Create null item" << std::endl;

		pool_.push(obj);
	}

	timeStart_ = std::chrono::system_clock::now();
}

void ItemManager::Spawn()
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

		GameObject* item = pool_.top();
		pool_.pop();
		activeNum_++;

		int zone = spawnZone_(engine);
		int x = 0, y = 0;
		int halfWidth = windowWidth / 2, halfHeight = windowHeight / 2;

		switch (zone)
		{
		case 0:	// Up side
			x = spawnX_(engine);
			y = halfHeight + spawnOffset_ + int(x / 100.f);
			break;

		case 1:	// Right side
			y = spawnY_(engine);
			x = halfWidth + spawnOffset_ + int(y / 100.f);
			break;

		case 2:	// Down side
			x = spawnX_(engine);
			y = -halfHeight - spawnOffset_ - int(x / 100.f);
			break;

		case 3:	// Left side
			y = spawnY_(engine);
			x = -halfWidth - spawnOffset_ - int(y / 100.f);
			break;
		}

		AEVec2 playerPos = playerTrans->GetPosition();
		x += int(playerPos.x);
		y += int(playerPos.y);

		item->GetComponent<Transform>()->SetPosition(float(x), float(y));
		item->active_ = true;
	}
}

void ItemManager::Release(GameObject* obj)
{
	obj->GetComponent<RigidBody>()->ClearVelocity();
	obj->active_ = false;
	pool_.push(obj);
	activeNum_--;
}

void ItemManager::Clear()
{
	while (!pool_.empty())
		pool_.pop();
}
