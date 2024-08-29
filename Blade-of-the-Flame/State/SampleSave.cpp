#include "SampleSave.h"

#include "../Utils/Utils.h"
#include "../Manager/GameObjectManager.h"
#include "../Serializer/StateSerializer.h"

void SampleSave::Init()
{
	GameObject* obj = GameObjectManager::GetInstance().CreateObject("TestObj");

	obj->AddComponent<Transform>();
	obj->GetComponent<Transform>()->SetScale({ 100, 100 });

	obj->AddComponent<Sprite>();
	obj->GetComponent<Sprite>()->SetColor({ 200, 200, 200 });

	obj->AddComponent<RigidBody>();
	obj->GetComponent<RigidBody>()->SetUseAcceleration(false);

	obj->AddComponent<PlayerController>();
	PlayerController* pCtrl = obj->GetComponent<PlayerController>();
	pCtrl->SetRotKeys(PlayerController::LEFT, AEVK_Q);
	pCtrl->SetRotKeys(PlayerController::RIGHT, AEVK_E);
	pCtrl->SetStopKey(AEVK_SPACE);

	obj->AddComponent<Audio>();
	obj->GetComponent<Audio>()->SetAudio("Assets/bouken.mp3");

	obj->AddComponent<Player>();

	//GameObject* square1 = GameObjectManager::GetInstance().CreateObject("square1");

	//square1->AddComponent<Transform>();
	//square1->GetComponent<Transform>()->SetScale({ 100, 100 });

	//square1->AddComponent<Sprite>();
	//square1->GetComponent<Sprite>()->SetColor({ 200, 100, 20 });

	//square1->AddComponent<PlayerController>();
	//PlayerController* pCtrl = square1->GetComponent<PlayerController>();
	//pCtrl->SetRotKeys(PlayerController::LEFT, AEVK_Q);
	//pCtrl->SetRotKeys(PlayerController::RIGHT, AEVK_E);

	//square1->AddComponent<RigidBody>();

	//square1->AddComponent<BoxCollider>();
	//square1->GetComponent<BoxCollider>()->SetType(Collider::OBB_TYPE);

	//GameObject* square2 = GameObjectManager::GetInstance().CreateObject("square2");

	//square2->AddComponent<Transform>();
	//square2->GetComponent<Transform>()->SetScale({ 100, 100 });
	//square2->GetComponent<Transform>()->SetPosition({ 300, 300 });

	//square2->AddComponent<Sprite>();
	//square2->GetComponent<Sprite>()->SetColor({ 50, 100, 150 });

	//square2->AddComponent<RigidBody>();

	//square2->AddComponent<BoxCollider>();
}

void SampleSave::Update()
{
}

void SampleSave::Exit()
{
}
