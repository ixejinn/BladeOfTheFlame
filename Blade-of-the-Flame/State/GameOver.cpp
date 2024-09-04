#include "GameOver.h"

#include "../Manager/GameObjectManager.h"

void GameOver::Init()
{
	obj = GameObjectManager::GetInstance().CreateObject();
	obj->AddComponent<Transform>();
	obj->AddComponent<Sprite>();
	obj->AddComponent<Text>();
	Text* text_ = obj->GetComponent<Text>();
	text_->SetFont("Assets/Roboto-Bold.ttf");
	text_->SetSize(1.f);
}

void GameOver::Update()
{
	obj->GetComponent<Text>()->SetString("GAME OVER!");
}

void GameOver::Exit()
{
}
