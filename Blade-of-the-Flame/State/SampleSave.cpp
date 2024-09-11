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
	GameObject* player = GameObjectManager::GetInstance().CreateObject("player");
	player->AddComponent<Player>();

	GameObject* boss = GameObjectManager::GetInstance().CreateObject("boss");
	boss->AddComponent<Boss1>();
	boss->active_ = true;

}

void SampleSave::Update()
{
}

void SampleSave::Exit()
{
	GameObjectManager::GetInstance().Clear();
}