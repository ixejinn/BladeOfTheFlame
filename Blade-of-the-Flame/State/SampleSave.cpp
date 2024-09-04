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
	
	GameObject* altar = GameObjectManager::GetInstance().CreateObject("flameAltar");
	altar->AddComponent<FlameAltar>();

	GameObject* compass = GameObjectManager::GetInstance().CreateObject("compass");
	compass->AddComponent<Compass>();
	compass->GetComponent<Compass>()->SetDestination(altar);

	MonsterManager::GetInstance().Initialize(5);
	ExpItemManager::GetInstance().Initialize(20);
	ItemManager::GetInstance().Initialize(3);

	GameObject* monsterBar = GameObjectManager::GetInstance().CreateObject("monsterBar");
	monsterBar->AddComponent<FillBar>();
	FillBar* monsterBarPtr = monsterBar->GetComponent<FillBar>();
	monsterBarPtr->SetShowType(FillBar::MONSTER_CNT);
	monsterBarPtr->SetFillColor({ 200, 200, 200 });

	GameObject* expBar = GameObjectManager::GetInstance().CreateObject("expBar");
	expBar->AddComponent<FillBar>();
	FillBar* expBarPtr = expBar->GetComponent<FillBar>();
	expBarPtr->SetShowType(FillBar::PLAYER_EXP);
	expBarPtr->SetFillColor({ 0, 255, 0 });

	GameObject* healthBar = GameObjectManager::GetInstance().CreateObject("healthBar");
	healthBar->AddComponent<FillBar>();
	FillBar* healthBarPtr = healthBar->GetComponent<FillBar>();
	healthBarPtr->SetShowType(FillBar::PLAYER_HP);
	healthBarPtr->SetFillColor({ 255, 0, 0 });
}

void SampleSave::Update()
{
	MonsterManager::GetInstance().Spawn();
	ItemManager::GetInstance().Spawn();
}

void SampleSave::Exit()
{
}