#include "SampleSave.h"

#include <string>
#include "../Manager/GameObjectManager.h"
#include "../Manager/MonsterManager.h"
#include "../Manager/ExpItemManager.h"
#include "../Manager/ItemManager.h"
#include "../Manager/EventManager.h"
#include "../Manager/CollisionManager.h"

void SampleSave::Init()
{
	GameObject* player = GameObjectManager::GetInstance().CreateObject("player");
	player->AddComponent<Player>();

	//GameObject* obj = GameObjectManager::GetInstance().CreateObject("test");
	//obj->AddComponent<Transform>();
	//obj->GetComponent<Transform>()->SetScale({ 100, 100 });
	//obj->AddComponent<Sprite>();

	//GameObject* boss = GameObjectManager::GetInstance().CreateObject("boss");
	//boss->AddComponent<Boss1>();
	//boss->active_ = true;

	GameObject* monster = GameObjectManager::GetInstance().CreateObject("monster");
	monster->AddComponent<Monster>();
	monster->GetComponent<Transform>()->SetPosition(100, 100);

	GameObject* healthBar = GameObjectManager::GetInstance().CreateObject("healthBar");
	healthBar->AddComponent<FillBar>();
	FillBar* healthBarPtr = healthBar->GetComponent<FillBar>();
	healthBarPtr->SetShowType(FillBar::PLAYER_HP);
}

void SampleSave::Update()
{
	//MonsterManager::GetInstance().Spawn();
}

void SampleSave::Exit()
{
	EventManager::GetInstance().DeleteAllRegisteredEntity();
	ItemManager::GetInstance().Clear();
	ExpItemManager::GetInstance().Clear();
	MonsterManager::GetInstance().Clear();
	GameObjectManager::GetInstance().Clear();
	CollisionManager::GetInstance().Clear();
	ParticleSystem::Delete();
}