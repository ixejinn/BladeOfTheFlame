#include "MonsterManager.h"

#include <string>
#include <typeindex>
#include "EventManager.h"
#include "../Component/LogicComponents/Monsters/NormalMonster.h"
#include "../Event/Event.h"

namespace Manager
{
	extern GameObjectManager& objMgr;
	extern EventManager& evntMgr;
}

MonsterManager::MonsterManager() : normalSpawner_(), instakillSpawner_()
{
	Manager::evntMgr.RegisterEntity(std::type_index(typeid(LevelUpEvent)), static_cast<EventEntity*>(this));
	Manager::evntMgr.RegisterEntity(std::type_index(typeid(SpawnBossEvent)), static_cast<EventEntity*>(this));
}

void MonsterManager::Initialize(int maxNum, int maxActiveNum, double spawnPeriod, int spawnNumPerWave)
{
	capturedCount_ = 0;
	normalSpawner_.Initialize(maxNum, maxActiveNum, spawnPeriod, spawnNumPerWave);
	instakillSpawner_.Initialize(5, 1, 10, 1);
}

void MonsterManager::Spawn()
{
	normalSpawner_.Spawn();
	instakillSpawner_.Spawn();
}

void MonsterManager::Release(MonsterType type, GameObject* obj)
{
	switch (type)
	{
	case NORMAL:
		normalSpawner_.Release(obj);
		break;

	case INSTAKILL:
		instakillSpawner_.Release(obj);
		break;
	}
}

void MonsterManager::Clear()
{
	normalSpawner_.Clear();
	instakillSpawner_.Clear();
}

void MonsterManager::OnEvent(BaseEvent* event)
{
	if (dynamic_cast<LevelUpEvent*>(event))
	{
		LevelUpEvent* lvlUp = static_cast<LevelUpEvent*>(event);
		normalSpawner_.SetMaxActiveNum(10 * lvlUp->level);
	}
	else if (dynamic_cast<SpawnBossEvent*>(event))
	{
		normalSpawner_.SetMaxActiveNum(100);
	}
}

void MonsterManager::OnCollision(CollisionEvent*)
{
}
