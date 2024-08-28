#include "SampleSave.h"

#include "../Utils/Utils.h"
#include "../Manager/GameObjectManager.h"
#include "../Serializer/StateSerializer.h"

void SampleSave::Init()
{
	obj = GameObjectManager::GetInstance().CreateObject("TestObj");

	obj->AddComponent<Transform>();
	obj->GetComponent<Transform>()->SetScale({ 90, 90 });

	obj->AddComponent<Sprite>();
	obj->GetComponent<Sprite>()->SetTexture("Assets/PlanetTexture.png");

	obj->AddComponent<RigidBody>();
	obj->GetComponent<RigidBody>()->SetDragCoefficient(0.f);
	//obj->GetComponent<RigidBody>()->SetUseAcceleration(false);

	/*obj->AddComponent<PlayerController>();
	PlayerController* pCtrl = obj->GetComponent<PlayerController>();
	pCtrl->SetRotKeys(PlayerController::LEFT, AEVK_Q);
	pCtrl->SetRotKeys(PlayerController::RIGHT, AEVK_E);
	pCtrl->SetStopKey(AEVK_SPACE);*/

	obj->AddComponent<Audio>();
	obj->GetComponent<Audio>()->SetAudio("Assets/bouken.mp3");

	obj->AddComponent<CircleCollider>();

	obj->AddComponent<Ball>();

	// racket
	GameObject* obj2 = GameObjectManager::GetInstance().CreateObject("TestObj2");

	obj2->AddComponent<Transform>();
	obj2->GetComponent<Transform>()->SetScale({ 30, 110 });
	obj2->GetComponent<Transform>()->SetPosition({ -windowWidth / 2.f + 100, 0 });

	obj2->AddComponent<Sprite>();
	obj2->GetComponent<Sprite>()->SetColor({ 100, 100, 100 });

	obj2->AddComponent<RigidBody>();
	obj2->GetComponent<RigidBody>()->SetUseAcceleration(false);
	obj2->GetComponent<RigidBody>()->SetDragCoefficient(10.f);

	obj2->AddComponent<PlayerController>();
	PlayerController* pCtrl = obj2->GetComponent<PlayerController>();
	pCtrl->SetOnlyUpDown(true);
	pCtrl->SetMoveSpeed(120.f);
	
	obj2->AddComponent<BoxCollider>();

	obj2->AddComponent<Racket>();

	// wall up
	GameObject* wallUp = GameObjectManager::GetInstance().CreateObject("WalUp");

	wallUp->AddComponent<Transform>();
	wallUp->GetComponent<Transform>()->SetScale({ windowWidth, 20 });
	wallUp->GetComponent<Transform>()->SetPosition({ 0, windowHeight / 2 - 10 });

	wallUp->AddComponent<Sprite>();
	wallUp->GetComponent<Sprite>()->SetColor({ 100, 100, 100 });

	wallUp->AddComponent<RigidBody>();
	wallUp->GetComponent<RigidBody>()->SetUseAcceleration(false);

	wallUp->AddComponent<BoxCollider>();

	wallUp->AddComponent<Wall>();

	// wall down
	GameObject* wallDown = GameObjectManager::GetInstance().CreateObject("WallDown");

	wallDown->AddComponent<Transform>();
	wallDown->GetComponent<Transform>()->SetScale({ windowWidth, 20 });
	wallDown->GetComponent<Transform>()->SetPosition({ 0, -windowHeight / 2 + 10 });

	wallDown->AddComponent<Sprite>();
	wallDown->GetComponent<Sprite>()->SetColor({ 100, 100, 100 });

	wallDown->AddComponent<RigidBody>();
	wallDown->GetComponent<RigidBody>()->SetUseAcceleration(false);

	wallDown->AddComponent<BoxCollider>();

	wallDown->AddComponent<Wall>();

	StateSerializer::GetInstance().SaveState("Sample.json");
}

void SampleSave::Update()
{
}

void SampleSave::Exit()
{
}
