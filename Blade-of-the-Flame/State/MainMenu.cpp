#include "MainMenu.h"

#include "../Manager/GameObjectManager.h"
//#include "../Manager/ResourceManager.h"

void MainMenu::Init()
{
	InitBackground();

	// Game button
	GameObject* gameBtn = GameObjectManager::GetInstance().CreateObject("gameBtn");
	gameBtn->AddComponent<Button>();

	Button* btn = gameBtn->GetComponent<Button>();
	btn->SetTodo(Button::GAME);
	btn->SetPosition({ 0, -200 });
	btn->SetScale({ 250, 80 });
	btn->SetText("GAME");

	// Exit button
	GameObject* exitBtn = GameObjectManager::GetInstance().CreateObject("exitBtn");
	exitBtn->AddComponent<Button>();

	btn = exitBtn->GetComponent<Button>();
	btn->SetTodo(Button::EXIT);
	btn->SetPosition({ 0, -325 });
	btn->SetScale({ 250, 80 });
	btn->SetText("EXIT");
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
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	GameObject* background = GameObjectManager::GetInstance().CreateObject("background");
	background->AddComponent<Transform>();
	//background->AddComponent<Sprite>();
	//background->AddComponent<Audio>();

	background->GetComponent<Transform>()->SetScale({ windowWidth, windowHeight });

	//Sprite* sp = background->GetComponent<Sprite>();
	//sp->SetTexture("Assets/Realmap.png");
	//sp->SetColor({ 255, 255, 255 });

	//Audio* audio = background->GetComponent<Audio>();
	//audio->SetAudio("Assets/bouken.mp3");	// 임시로 넣어둠

	// Game logo
	GameObject* gameLogo = GameObjectManager::GetInstance().CreateObject("gameLogo");
	gameLogo->AddComponent<Transform>();
	gameLogo->AddComponent<Sprite>();

	Transform* trans = gameLogo->GetComponent<Transform>();
	trans->SetPosition({ 0, 180 });
	trans->SetScale({ 538, 200 });

	Sprite* sp = gameLogo->GetComponent<Sprite>();
	sp->SetTexture("Assets/Logo/GameLogo.png");
}
