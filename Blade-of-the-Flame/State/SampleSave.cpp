#include "SampleSave.h"

#include <string>
#include "../Utils/Utils.h"
#include "../Utils/RandomEngine.h"
#include "../Manager/GameObjectManager.h"
#include "../Manager/MonsterManager.h"
#include "../Manager/ExpItemManager.h"
#include "../Manager/ItemManager.h"
#include "../Serializer/StateSerializer.h"

void SampleSave::Init()
{
	GameObject* obj = GameObjectManager::GetInstance().CreateObject("player");
	obj->AddComponent<Player>();
	
	MonsterManager::GetInstance().Initialize(5);
	ExpItemManager::GetInstance().Initialize(20);
	ItemManager::GetInstance().Initialize(3);

	// boss ¸¸µé°í inactive
}

void SampleSave::Update()
{
	MonsterManager::GetInstance().Spawn();
	ItemManager::GetInstance().Spawn();
}

void SampleSave::Exit()
{
}