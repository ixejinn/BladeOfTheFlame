#include "MainMenu.h"

#include "../Manager/GameObjectManager.h"
#include "../Manager/GameStateManager.h"
#include "../State/GameState.h"

namespace Manager
{
	extern GameObjectManager& objMgr;
	extern GameStateManager& gsMgr;
}

void MainMenu::Init()
{
	InitBackground();

	// START button
	GameObject* start = Manager::objMgr.CreateObject("restartClear");
	start->AddComponent<Button>();

	startBtn_ = start->GetComponent<Button>();
	startBtn_->SetPosition({ 0, -180 });
	//startBtn_->SetScale({ 250, 80 });
	startBtn_->SetScale({ 300, 100 });
	startBtn_->SetText("GAME");

	// EXIT button
	GameObject* exit = Manager::objMgr.CreateObject("exitClear");
	exit->AddComponent<Button>();

	exitBtn_ = exit->GetComponent<Button>();
	exitBtn_->SetPosition({ 0, -300 });
	exitBtn_->SetScale({ 300, 100 });
	exitBtn_->SetText("EXIT");
}

void MainMenu::Update()
{
	if (startBtn_->IsClicked())
	{
		GameState* gameState = new GameState();
		Manager::gsMgr.ChangeState(gameState);
	}
	else if (exitBtn_->IsClicked())
		Manager::gsMgr.ChangeState(nullptr);
}

void MainMenu::Exit()
{
	Manager::objMgr.Clear();
}

void MainMenu::InitBackground()
{
	// Background
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	// Game logo
	GameObject* gameLogo = Manager::objMgr.CreateObject("gameLogo");
	gameLogo->AddComponent<Transform>();
	gameLogo->AddComponent<Sprite>();

	Transform* trans = gameLogo->GetComponent<Transform>();
	trans->SetPosition({ 0, 180 });
	//trans->SetScale({ 538, 200 });
	trans->SetScale({ 538 * 1.5f, 200 * 1.5f });

	Sprite* sp = gameLogo->GetComponent<Sprite>();
	sp->SetTexture("Assets/Logo/GameLogo.png");
}
