#include "GameClear.h"

#include "../Manager/GameObjectManager.h"

void GameClear::Init()
{
	obj = GameObjectManager::GetInstance().CreateObject();
	obj->AddComponent<Transform>();
	obj->AddComponent<Sprite>();
	obj->AddComponent<Text>();

	Text* text = obj->GetComponent<Text>();
	text->SetFont("Assets/Roboto-Bold.ttf");
	text->SetSize(1.f);
	text->SetString("GAME CLEAR!");
}

void GameClear::Update()
{
}

void GameClear::Exit()
{
}
