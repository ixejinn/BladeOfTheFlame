#include "MainMenu.h"

#include "../Manager/GameObjectManager.h"

void MainMenu::Init()
{
	InitBackground();

	GameObject* gameBtn = GameObjectManager::GetInstance().CreateObject("btn");
	gameBtn->AddComponent<Button>();

	Button* btn = gameBtn->GetComponent<Button>();
	btn->SetTodo(Button::GAME);
	btn->SetPosition({ 0, 0 });
	btn->SetScale({ 100, 100 });
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
	// Background
	GameObject* background = GameObjectManager::GetInstance().CreateObject("background");
	background->AddComponent<Transform>();
	background->AddComponent<Sprite>();
	background->AddComponent<Audio>();

	background->GetComponent<Transform>()->SetScale({ windowWidth, windowHeight });

	Sprite* sp = background->GetComponent<Sprite>();
	//sp->SetTexture("Assets/Realmap.png");
	sp->SetColor({ 255, 255, 255 });

	Audio* audio = background->GetComponent<Audio>();
	audio->SetAudio("Assets/bouken.mp3");	// 임시로 넣어둠

	// Game logo
	GameObject* gameLogo = GameObjectManager::GetInstance().CreateObject("gameLogo");
	gameLogo->AddComponent<Transform>();
	gameLogo->AddComponent<Sprite>();

	Transform* trans = gameLogo->GetComponent<Transform>();
	trans->SetPosition({ 0, 200 });
	//trans->SetScale({})

	sp = gameLogo->GetComponent<Sprite>();
	//sp->SetTexture()
	sp->SetColor({ 255, 255, 255 });
}
