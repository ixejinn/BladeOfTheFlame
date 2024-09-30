#include "GameState.h"

#include "../Manager/GameObjectManager.h"
#include "../Manager/MonsterManager.h"
#include "../Manager/ExpItemManager.h"
#include "../Manager/ItemManager.h"
#include "../Manager/EventManager.h"
#include "../Manager/CollisionManager.h"
#include "../Manager/ParticleSystem.h"
#include "../Manager/EnvironmentManager.h"

namespace Manager
{
	extern GameObjectManager& objMgr;
}

void GameState::Init()
{
#ifndef _DEBUG
	//InitBackground();
	EnvironmentManager& envMgr = EnvironmentManager::GetInstance();
#endif

	/* PLAYER */
	GameObject* player = Manager::objMgr.CreateObject("player");
	player->AddComponent<Player>();

#ifndef _DEBUG
	envMgr.SetPlayerTransform();
#endif

	/* FLAME ALTAR */
	GameObject* altar = Manager::objMgr.CreateObject("flameAltar");
	altar->AddComponent<FlameAltar>();

	/* COMPASS */
	GameObject* compass = Manager::objMgr.CreateObject("compass");
	compass->AddComponent<Compass>();
	compass->GetComponent<Compass>()->SetDestination(altar);

	/* BOSS */
	GameObject* boss1 = Manager::objMgr.CreateObject("boss");
	boss1->AddComponent<Boss1>();

	///////////////////////////지울수도 있음/////////////////////////////
	GameObject* boss2 = Manager::objMgr.CreateObject("boss2");
	boss2->AddComponent<Boss2>();
	boss2->active_ = false;
	////////////////////////////////////////////////////////////////////

	/* SPAWN MANAGERS */
	MonsterManager::GetInstance().Initialize(320, 20, 5.0, 10);
	ExpItemManager::GetInstance().Initialize(230);
	ItemManager::GetInstance().Initialize(20, 6, 20.0, 3);

#ifndef _DEBUG
	/* SCREEN OVERLAY EFFECT */
	GameObject* effect = Manager::objMgr.CreateObject("ScreenEffect");
	effect->AddComponent<ScreenOverlay>();
#endif

	SetFillBar();
}

void GameState::Update()
{
#ifndef _DEBUG
	EnvironmentManager::GetInstance().Update();
#endif

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
	ParticleSystem::Delete();
}

void GameState::SetFillBar()
{
	GameObject* bossBar = Manager::objMgr.CreateObject("bossBar");
	bossBar->AddComponent<FillBar>();
	FillBar* bossBarPtr = bossBar->GetComponent<FillBar>();
	bossBarPtr->SetBoss(Manager::objMgr.GetObjectA("boss")->GetComponent<Boss1>());
	bossBarPtr->SetShowType(FillBar::BOSS_HP);

	GameObject* monsterBar = Manager::objMgr.CreateObject("monsterBar");
	monsterBar->AddComponent<FillBar>();
	monsterBar->GetComponent<FillBar>()->SetShowType(FillBar::MONSTER_CNT);

	GameObject* expBar = Manager::objMgr.CreateObject("expBar");
	expBar->AddComponent<FillBar>();
	expBar->GetComponent<FillBar>()->SetShowType(FillBar::PLAYER_EXP);

	GameObject* healthBar = Manager::objMgr.CreateObject("healthBar");
	healthBar->AddComponent<FillBar>();
	healthBar->GetComponent<FillBar>()->SetShowType(FillBar::PLAYER_HP);

	GameObject* skillBar = Manager::objMgr.CreateObject("skillBar");
	skillBar->AddComponent<FillBar>();
	skillBar->GetComponent<FillBar>()->SetShowType(FillBar::SKILL);
}
