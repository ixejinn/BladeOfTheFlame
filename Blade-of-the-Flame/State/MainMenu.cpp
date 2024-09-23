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
	GameObject* start = Manager::objMgr.CreateObject("start");
	start->AddComponent<Button>();

	startBtn_ = start->GetComponent<Button>();
	startBtn_->SetPosition({ 0, -200 });
	startBtn_->SetScale({ 250, 80 });
	startBtn_->SetText("GAME");

	// EXIT button
	GameObject* exit = Manager::objMgr.CreateObject("exit");
	exit->AddComponent<Button>();

	exitBtn_ = exit->GetComponent<Button>();
	exitBtn_->SetPosition({ 0, -325 });
	exitBtn_->SetScale({ 250, 80 });
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
	trans->SetScale({ 538, 200 });

	Sprite* sp = gameLogo->GetComponent<Sprite>();
	sp->SetTexture("Assets/Logo/GameLogo.png");
}
