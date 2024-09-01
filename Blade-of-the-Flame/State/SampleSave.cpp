#include "SampleSave.h"

#include <string>
#include "../Utils/Utils.h"
#include "../Utils/RandomEngine.h"
#include "../Manager/GameObjectManager.h"
#include "../Manager/MonsterManager.h"
#include "../Serializer/StateSerializer.h"

void SampleSave::Init()
{
	GameObject* obj = GameObjectManager::GetInstance().CreateObject("player");
	obj->AddComponent<Player>();

	//GameObject* monster = GameObjectManager::GetInstance().CreateObject("mon");
	//monster->AddComponent<Monster>();
	//monster->GetComponent<Transform>()->SetPosition(0.1, 0.1);
	
	MonsterManager::GetInstance().Initialize(100);

	// boss ¸¸µé°í inactive
}

void SampleSave::Update()
{
	MonsterManager::GetInstance().SpawnMonster();
}

void SampleSave::Exit()
{
}
