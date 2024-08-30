#include "SampleSave.h"

#include <string>
#include "../Utils/Utils.h"
#include "../Utils/RandomEngine.h"
#include "../Manager/GameObjectManager.h"
#include "../Serializer/StateSerializer.h"

void SampleSave::Init()
{
	GameObject* obj = GameObjectManager::GetInstance().CreateObject("player");

	obj->AddComponent<Transform>();
	obj->GetComponent<Transform>()->SetScale({ 30, 100 });

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

	auto& engine = RandomEngine::GetInstance().GetEngine();
	std::uniform_int_distribution<int> coord{ -300, 300 };

	GameObject* monster[5];
	for (int i = 0; i < 5; i++)
	{
		monster[i] = GameObjectManager::GetInstance().CreateObject("monster" + std::to_string(i));

		monster[i]->AddComponent<Monster>();
		monster[i]->GetComponent<Transform>()->SetScale({ 100, 100 });
		int x = coord(engine), y = coord(engine);
		monster[i]->GetComponent<Transform>()->SetPosition(x, y);
		monster[i]->GetComponent<Sprite>()->SetColor({ 200, 100, 20 });
	}
}

void SampleSave::Update()
{
}

void SampleSave::Exit()
{
}
