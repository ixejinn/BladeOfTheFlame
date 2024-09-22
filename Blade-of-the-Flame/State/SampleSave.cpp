#include "SampleSave.h"

#include <string>
#include "../Manager/GameObjectManager.h"
#include "../Manager/MonsterManager.h"
#include "../Manager/ExpItemManager.h"
#include "../Manager/ItemManager.h"
#include "../Manager/EventManager.h"
#include "../Manager/CollisionManager.h"
#include "../Manager/EnvironmentManager.h"

GameObject* player;
GameObject* darkness;

void SampleSave::Init()
{
	//GameObject* background = GameObjectManager::GetInstance().CreateObject("background");
	//background->AddComponent<Transform>();
	//background->AddComponent<Sprite>();
	//background->AddComponent<Audio>();

	////background->GetComponent<Transform>()->SetScale({ windowWidth, windowHeight });
	//background->GetComponent<Transform>()->SetScale({ windowWidth * 9, windowHeight * 9 });

	//Sprite* sp = background->GetComponent<Sprite>();
	//sp->SetTexture("Assets/Realmap.png");

	EnvironmentManager::GetInstance();

	player = GameObjectManager::GetInstance().CreateObject("player");
	player->AddComponent<Player>();

	EnvironmentManager::GetInstance().SetPlayerTransform();

	GameObject* obj = GameObjectManager::GetInstance().CreateObject("test");
	obj->AddComponent<Transform>();
	obj->GetComponent<Transform>()->SetScale({ 100, 100 });
	obj->AddComponent<Sprite>();
	obj->GetComponent<Sprite>()->SetTexture("Assets/PlanetTexture.png");
	obj->GetComponent<Sprite>()->SetAlpha(0.5);

	//GameObject* boss = GameObjectManager::GetInstance().CreateObject("boss");
	//boss->AddComponent<Boss1>();
	//boss->active_ = true;

	//GameObject* monster = GameObjectManager::GetInstance().CreateObject("monster");
	//monster->AddComponent<Monster>();
	//monster->GetComponent<Transform>()->SetPosition(100, 100);

	GameObject* healthBar = GameObjectManager::GetInstance().CreateObject("healthBar");
	healthBar->AddComponent<FillBar>();
	FillBar* healthBarPtr = healthBar->GetComponent<FillBar>();
	healthBarPtr->SetShowType(FillBar::PLAYER_HP);

	//MonsterManager::GetInstance().Initialize(10);
	//ExpItemManager::GetInstance().Initialize(20);

	//MonsterManager::GetInstance().SetMaxActiveNum(5);

	//darkness = GameObjectManager::GetInstance().CreateObject("darkness");
	//darkness->AddComponent<Transform>();
	//darkness->AddComponent<Sprite>();
	//darkness->GetComponent<Transform>()->SetScale({ 1600, 900 });
	//darkness->GetComponent<Sprite>()->SetTexture("Assets/dark75.png");
}

void SampleSave::Update()
{
	EnvironmentManager::GetInstance().Update();
	//MonsterManager::GetInstance().Spawn();
	//darkness->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());
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