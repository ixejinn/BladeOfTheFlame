#include "SampleSave.h"

#include "../Utils/Utils.h"
#include "../Manager/GameObjectManager.h"
#include "../Serializer/StateSerializer.h"

void SampleSave::Init()
{
	GameObject* obj = GameObjectManager::GetInstance().CreateObject("TestObj");

	obj->AddComponent<Transform>();
	obj->GetComponent<Transform>()->SetScale({ 10, 10 });

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
}

void SampleSave::Update()
{

}

void SampleSave::Exit()
{

}
