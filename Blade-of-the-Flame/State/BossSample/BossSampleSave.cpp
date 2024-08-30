#include "BossSampleSave.h"
#include "../../Utils/Utils.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Serializer/StateSerializer.h"
//TEST_PLAYER
#include "../SampleSave.h"

void BossSampleSave::Init()
{
	// -----------------------------------------------------------------------------------------
	//PLAYER_TEST
	GameObject* obj = GameObjectManager::GetInstance().CreateObject("TestObj");

	obj->AddComponent<Transform>();
	obj->GetComponent<Transform>()->SetScale({ 50, 50 });
	
	obj->AddComponent<Sprite>();
	obj->GetComponent<Sprite>()->SetTexture("Assets/PlanetTexture.png");

	obj->AddComponent<RigidBody>();

	obj->AddComponent<PlayerController>();
	PlayerController* pCtrl = obj->GetComponent<PlayerController>();

	pCtrl->SetRotKeys(PlayerController::LEFT, AEVK_Q);
	pCtrl->SetRotKeys(PlayerController::RIGHT, AEVK_E);
	pCtrl->SetStopKey(AEVK_SPACE);

	obj->AddComponent<Audio>();
	obj->GetComponent<Audio>()->SetAudio("Assets/bouken.mp3");
	// -----------------------------------------------------------------------------------------
	//BOSS_TEST
	GameObject* boss1 = GameObjectManager::GetInstance().CreateObject("boss");

	boss1->AddComponent<Transform>();
	boss1->AddComponent<Sprite>	  ();
	boss1->AddComponent<RigidBody>();
	boss1->AddComponent<Boss1>    ();

	boss1->GetComponent<Transform>()->SetScale({ 200, 200 });
	boss1->GetComponent<Transform>()->SetPosition({ 400,400 });

	boss1->GetComponent<Sprite>	  ()->SetTexture("Assets/yee.png");

	// -----------------------------------------------------------------------------------------
	//BULLET_TEST
	GameObject* bullet = GameObjectManager::GetInstance().CreateObject("bullet");
	bullet->AddComponent<Transform> ();
	bullet->AddComponent<Sprite>    ();
	bullet->AddComponent<RigidBody> ();
	bullet->AddComponent<BulletComp>();

	bullet->GetComponent<Transform>()->SetScale({ 50, 50 });
	bullet->GetComponent<Sprite>   ()->SetTexture("Assets/YeeHead.png");
}

void BossSampleSave::Update()
{

}

void BossSampleSave::Exit()
{

}
