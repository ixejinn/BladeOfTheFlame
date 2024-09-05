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
	GameObject* obj = GameObjectManager::GetInstance().CreateObject("btn");
	obj->AddComponent<Button>();
	
	Button* btn = obj->GetComponent<Button>();
	btn->SetPosition({ 0, 100 });
	btn->SetScale({ 100, 200 });

}

void SampleSave::Update()
{
}

void SampleSave::Exit()
{
	GameObjectManager::GetInstance().Clear();
}