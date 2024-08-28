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
	obj->GetComponent<Sprite>()->SetTexture("Assets/PlanetTexture.png");

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

	GameObject* square = GameObjectManager::GetInstance().CreateObject("square");

	square->AddComponent<Transform>();
	square->GetComponent<Transform>()->SetScale({ 100, 100 });

	square->AddComponent<Sprite>();
	square->GetComponent<Sprite>()->SetColor({ 200, 100, 20 });
}

void SampleSave::Update()
{
}

void SampleSave::Exit()
{
}
