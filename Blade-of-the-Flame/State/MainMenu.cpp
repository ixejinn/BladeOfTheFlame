#include "MainMenu.h"

#include "../Manager/GameObjectManager.h"

void MainMenu::Init()
{
	InitBackground();

	GameObject* obj = GameObjectManager::GetInstance().CreateObject("btn");
	obj->AddComponent<Button>();

	Button* btn = obj->GetComponent<Button>();
	btn->SetPosition({ 0, 100 });
	btn->SetScale({ 100, 200 });
}

void MainMenu::Update()
{
}

void MainMenu::Exit()
{
	GameObjectManager::GetInstance().Clear();
}

void MainMenu::InitBackground()
{
	GameObject* background = GameObjectManager::GetInstance().CreateObject("background");
	background->AddComponent<Transform>();
	background->AddComponent<Sprite>();
	background->AddComponent<Audio>();

	background->GetComponent<Transform>()->SetScale({ windowWidth, windowHeight });

	Sprite* sp = background->GetComponent<Sprite>();
	sp->SetTexture("Assets/Realmap.png");

	//Audio* audio = background->GetComponent<Audio>();
	//audio->SetAudio("Assets/bouken.mp3");
}
