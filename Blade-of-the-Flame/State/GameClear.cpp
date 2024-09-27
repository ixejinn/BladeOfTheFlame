#include "GameClear.h"

#include "MainMenu.h"
#include "../Component/Button.h"
#include "../Manager/GameObjectManager.h"
#include "../Manager/GameStateManager.h"

namespace Manager
{
	extern GameObjectManager& objMgr;
	extern GameStateManager& gsMgr;
}

void GameClear::Init()
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	GameObject* message = GameObjectManager::GetInstance().CreateObject();
	message->AddComponent<Text>();

	Text* messageText = message->GetComponent<Text>();
	messageText->SetFont("Assets/Roboto-Bold.ttf");
	messageText->SetSize(1.f);
	messageText->SetString("GAME CLEAR!");

	// MAINMENU button
	GameObject* main = Manager::objMgr.CreateObject("restart");
	main->AddComponent<Button>();

	mainBtn_ = main->GetComponent<Button>();
	mainBtn_->SetPosition({ 0, -180 });
	mainBtn_->SetScale({ 300, 100 });
	mainBtn_->SetText("RESTART");

	// EXIT button
	GameObject* exit = Manager::objMgr.CreateObject("exit");
	exit->AddComponent<Button>();

	exitBtn_ = exit->GetComponent<Button>();
	exitBtn_->SetPosition({ 0, -300 });
	exitBtn_->SetScale({ 300, 100 });
	exitBtn_->SetText("EXIT");
}

void GameClear::Update()
{
	if (mainBtn_->IsClicked())
	{
		MainMenu* menu = new MainMenu();
		Manager::gsMgr.ChangeState(menu);
	}
	else if (exitBtn_->IsClicked())
		Manager::gsMgr.ChangeState(nullptr);
}

void GameClear::Exit()
{
	Manager::objMgr.Clear();
}
