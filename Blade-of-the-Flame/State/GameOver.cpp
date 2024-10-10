#include "GameOver.h"

#include "MainMenu.h"
#include "../Component/Button.h"
#include "../Manager/GameObjectManager.h"
#include "../Manager/GameStateManager.h"

namespace Manager
{
	extern GameObjectManager& objMgr;
	extern GameStateManager& gsMgr;
}

void GameOver::Init()
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	GameObject* message = GameObjectManager::GetInstance().CreateObject();
	message->AddComponent<Transform>();
	message->AddComponent<Sprite>();

	Transform* trans = message->GetComponent<Transform>();
	trans->SetPosition(0, 0);
	trans->SetScale({ 682, 260 });

	message->GetComponent<Sprite>()->SetTexture("Assets/gameover.png");

	// MAINMENU button
	GameObject* main = Manager::objMgr.CreateObject("restartOver");
	main->AddComponent<Button>();

	mainBtn_ = main->GetComponent<Button>();
	mainBtn_->SetPosition({ 0, -180 });
	mainBtn_->SetScale({ 300, 100 });
	mainBtn_->SetText("RESTART");

	// EXIT button
	GameObject* exit = Manager::objMgr.CreateObject("exitOver");
	exit->AddComponent<Button>();

	exitBtn_ = exit->GetComponent<Button>();
	exitBtn_->SetPosition({ 0, -300 });
	exitBtn_->SetScale({ 300, 100 });
	exitBtn_->SetText("EXIT");
}

void GameOver::Update()
{
	if (mainBtn_->IsClicked())
	{
		MainMenu* menu = new MainMenu();
		Manager::gsMgr.ChangeState(menu);
	}
	else if (exitBtn_->IsClicked())
		Manager::gsMgr.ChangeState(nullptr);
}

void GameOver::Exit()
{
	Manager::objMgr.Clear();
}
