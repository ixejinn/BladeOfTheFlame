#include "SampleSave.h"

#include <string>
#include "AEEngine.h"
#include "../Manager/GameObjectManager.h"
#include "../Manager/MonsterManager.h"
#include "../Manager/ExpItemManager.h"
#include "../Manager/ItemManager.h"
#include "../Manager/EventManager.h"
#include "../Manager/CollisionManager.h"
#include "../Manager/EnvironmentManager.h"
#include "../Manager/GameStateManager.h"
#include "../State/MainMenu.h"

GameObject* digiLogo;
GameObject* teamLogo;

void SampleSave::Init()
{
	digiLogo = GameObjectManager::GetInstance().CreateObject("digiLogo");
	digiLogo->AddComponent<Transform>();
	digiLogo->GetComponent<Transform>()->SetScale({ 762.5, 222.5 });
	digiLogo->AddComponent<AnimationComp>();
	digiLogo->GetComponent<Sprite>()->SetTexture("Assets/Logo/DigiPen_Singapore_WEB_BLACK.png");
	digiLogo->GetComponent<AnimationComp>()->SetType(AnimationComp::APPEAR);
	digiLogo->GetComponent<AnimationComp>()->SetTerm(50);

	teamLogo = GameObjectManager::GetInstance().CreateObject("teamLogo");
	teamLogo->AddComponent<Transform>();
	teamLogo->GetComponent<Transform>()->SetScale({ 753.8, 130.6 });
	teamLogo->AddComponent<AnimationComp>();
	teamLogo->GetComponent<Sprite>()->SetTexture("Assets/Logo/TeamLogo.png");
	teamLogo->GetComponent<AnimationComp>()->SetType(AnimationComp::APPEAR);
	teamLogo->GetComponent<AnimationComp>()->SetTerm(50);
	teamLogo->active_ = false;
}

void SampleSave::Update()
{
	//EnvironmentManager::GetInstance().Update();
	//MonsterManager::GetInstance().Spawn();
	//darkness->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());
	AnimationComp* ani = digiLogo->GetComponent<AnimationComp>();
	if (ani->GetType() == AnimationComp::APPEAR && ani->CurrentAnimationOver())
		ani->SetType(AnimationComp::DISAPPEAR);
	else if (ani->GetType() == AnimationComp::DISAPPEAR && ani->CurrentAnimationOver())
	{
		teamLogo->active_ = true;
		digiLogo->active_ = false;
	}

	ani = teamLogo->GetComponent<AnimationComp>();
	if (teamLogo->active_ && ani->GetType() == AnimationComp::APPEAR && ani->CurrentAnimationOver())
	{
		static double elapsedTime = 0.0;
		double dt = AEFrameRateControllerGetFrameRate();
		elapsedTime += dt;

		if (elapsedTime >= 4500)
			ani->SetType(AnimationComp::DISAPPEAR);
		else if (elapsedTime >= 2500)
			AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
		//ani->SetType(AnimationComp::DISAPPEAR);
	}
	else if (teamLogo->active_ && ani->GetType() == AnimationComp::DISAPPEAR && ani->CurrentAnimationOver())
	{
		MainMenu* mainMenu = new MainMenu();
		GameStateManager::GetInstance().ChangeState(mainMenu);
	}
}

void SampleSave::Exit()
{
	EventManager::GetInstance().DeleteAllRegisteredEntity();
	ItemManager::GetInstance().Clear();
	ExpItemManager::GetInstance().Clear();
	MonsterManager::GetInstance().Clear();
	GameObjectManager::GetInstance().Clear();
	CollisionManager::GetInstance().Clear();
	ParticleSystem::Delete();
}