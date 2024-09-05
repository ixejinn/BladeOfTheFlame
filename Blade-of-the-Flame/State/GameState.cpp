#include "GameState.h"

#include "../Manager/GameObjectManager.h"
#include "../Manager/MonsterManager.h"
#include "../Manager/ExpItemManager.h"
#include "../Manager/ItemManager.h"
#include "../Manager/EventManager.h"
#include "../Manager/CollisionManager.h"

void GameState::Init()
{
	InitBackground();

	// Player
	GameObject* player = GameObjectManager::GetInstance().CreateObject("player");
	player->AddComponent<Player>();

	// Flame altar
	GameObject* altar = GameObjectManager::GetInstance().CreateObject("flameAltar");
	altar->AddComponent<FlameAltar>();

	// Compass
	GameObject* compass = GameObjectManager::GetInstance().CreateObject("compass");
	compass->AddComponent<Compass>();
	compass->GetComponent<Compass>()->SetDestination(altar);

	// Boss
	GameObject* boss = GameObjectManager::GetInstance().CreateObject("boss");
	boss->AddComponent<Boss1>();

	// Spawn managers
	MonsterManager::GetInstance().Initialize(5);
	ExpItemManager::GetInstance().Initialize(20);
	ItemManager::GetInstance().Initialize(3);

	SetFillBar();
}

void GameState::Update()
{
	MonsterManager::GetInstance().Spawn();
	ItemManager::GetInstance().Spawn();
}

void GameState::Exit()
{
	EventManager::GetInstance().DeleteAllRegisteredEntity();
	ItemManager::GetInstance().Clear();
	ExpItemManager::GetInstance().Clear();
	MonsterManager::GetInstance().Clear();
	GameObjectManager::GetInstance().Clear();
	CollisionManager::GetInstance().Clear();

}

void GameState::InitBackground()
{
	GameObject* background = GameObjectManager::GetInstance().CreateObject("background");
	background->AddComponent<Transform>();
	background->AddComponent<Sprite>();
	background->AddComponent<Audio>();

	//background->GetComponent<Transform>()->SetScale({ windowWidth, windowHeight });
	background->GetComponent<Transform>()->SetScale({ windowWidth * 9, windowHeight * 9 });

	Sprite* sp = background->GetComponent<Sprite>();
	sp->SetTexture("Assets/Realmap.png");

	Audio* audio = background->GetComponent<Audio>();
	audio->SetAudio("Assets/bouken.mp3");
}

void GameState::SetFillBar()
{
	GameObject* monsterBar = GameObjectManager::GetInstance().CreateObject("monsterBar");
	monsterBar->AddComponent<FillBar>();
	FillBar* monsterBarPtr = monsterBar->GetComponent<FillBar>();
	monsterBarPtr->SetShowType(FillBar::MONSTER_CNT);

	GameObject* expBar = GameObjectManager::GetInstance().CreateObject("expBar");
	expBar->AddComponent<FillBar>();
	FillBar* expBarPtr = expBar->GetComponent<FillBar>();
	expBarPtr->SetShowType(FillBar::PLAYER_EXP);

	GameObject* healthBar = GameObjectManager::GetInstance().CreateObject("healthBar");
	healthBar->AddComponent<FillBar>();
	FillBar* healthBarPtr = healthBar->GetComponent<FillBar>();
	healthBarPtr->SetShowType(FillBar::PLAYER_HP);

	GameObject* bossBar = GameObjectManager::GetInstance().CreateObject("bossBar");
	bossBar->AddComponent<FillBar>();
	FillBar* bossBarPtr = bossBar->GetComponent<FillBar>();
	bossBarPtr->SetBoss(GameObjectManager::GetInstance().GetObjectA("boss")->GetComponent<Boss1>());
	bossBarPtr->SetShowType(FillBar::BOSS_HP);
}
