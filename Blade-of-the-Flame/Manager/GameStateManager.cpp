#include "GameStateManager.h"

#include "AEEngine.h"
#include "../State/State.h"
#include "../Manager/ComponentManager.h"
#include "../Manager/CollisionManager.h"
#include "../Manager/EventManager.h"
#include "../Component/EngineComponent.h"
#include "../Component/GraphicsComponent.h"
#include "../Component/LogicComponent.h"
#include "../Component/AudioComponent.h"

GameStateManager::GameStateManager() : preState_(nullptr), curState_(nullptr) {}

void GameStateManager::Clear()
{
	preState_ = nullptr;
	curState_ = nullptr;
}

void GameStateManager::Init()
{
	if (curState_)
		curState_->Init();
}

void GameStateManager::Update()
{
	if (curState_)
	{
		curState_->Update();

		ComponentManager<EngineComponent>::GetInstance().UpdateComponent();
		ComponentManager<GraphicsComponent>::GetInstance().UpdateComponent();
		ComponentManager<LogicComponent>::GetInstance().UpdateComponent();
		ComponentManager<AudioComponent>::GetInstance().UpdateComponent();

		CollisionManager::GetInstance().CheckAllCollision();
		EventManager::GetInstance().ProcessEvent();
	}
}

void GameStateManager::Exit()
{
	if (curState_)
		curState_->Exit();
}

void GameStateManager::ChangeState(State* newState)
{
	preState_ = curState_;
	Exit();

	// TODO: Clear Manager

	curState_ = newState;
	Init();
}
