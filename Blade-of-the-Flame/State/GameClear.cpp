#include "GameClear.h"

#include "../Manager/GameObjectManager.h"

void GameClear::Init()
{
	obj = GameObjectManager::GetInstance().CreateObject();
	obj->AddComponent<Transform>();
	obj->AddComponent<Sprite>();
	obj->AddComponent<Text>();
	Text* text_ = obj->GetComponent<Text>();
	text_->SetFont("Assets/Roboto-Bold.ttf");
	text_->SetSize(1.f);
}

void GameClear::Update()
{
	obj->GetComponent<Text>()->SetString("GAME CLEAR!");
}

void GameClear::Exit()
{
}
