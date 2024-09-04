#include "BossSampleSave.h"
#include "../../Utils/Utils.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Serializer/StateSerializer.h"
//TEST_PLAYER
#include "../SampleSave.h"
#include "../../Component/LogicComponents/Bullet.h"
#include "../../Component/LogicComponents/Boss1.h"

void BossSampleSave::Init()
{
	// -----------------------------------------------------------------------------------------
	//PLAYER_TEST
	GameObject* obj = GameObjectManager::GetInstance().CreateObject("player");
	obj->AddComponent<Player>();

	// -----------------------------------------------------------------------------------------
	//BOSS_TEST
	GameObject* boss1 = GameObjectManager::GetInstance().CreateObject("boss");
	boss1->AddComponent<Boss1>();

	GameObject* healthBar = GameObjectManager::GetInstance().CreateObject("healthBar");
	healthBar->AddComponent<FillBar>();
	FillBar* healthBarPtr = healthBar->GetComponent<FillBar>();
	healthBarPtr->SetShowType(FillBar::PLAYER_HP);
	healthBarPtr->SetFillColor({ 255, 0, 0 });

	GameObject* bossBar = GameObjectManager::GetInstance().CreateObject("bossBar");
	bossBar->AddComponent<FillBar>();
	FillBar* bossBarPtr = bossBar->GetComponent<FillBar>();
	bossBarPtr->SetShowType(FillBar::BOSS_HP);
	bossBarPtr->SetFillColor({ 255, 0, 0 });

	// -----------------------------------------------------------------------------------------
	//BULLET_TEST
	
}

void BossSampleSave::Update()
{

}

void BossSampleSave::Exit()
{

}
