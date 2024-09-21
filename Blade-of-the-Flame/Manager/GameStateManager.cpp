#include "GameStateManager.h"

#include "AEEngine.h"
#include "../State/State.h"
#include "../Manager/ComponentManager.h"
#include "../Manager/CollisionManager.h"
#include "../Manager/EventManager.h"
#include "../Manager/Camera.h"
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
	if (curState_ != preState_)
	{
		if (preState_ != nullptr)
		{
			preState_->Exit();
			delete preState_;
		}

		if (curState_ == nullptr)
			return;

		curState_->Init();
		preState_ = curState_;
	}

	if (curState_)
	{
		curState_->Update();

		ComponentManager<LogicComponent>::GetInstance().UpdateComponent();
		CollisionManager::GetInstance().CheckAllCollision();
		EventManager::GetInstance().ProcessEvent();

		ComponentManager<EngineComponent>::GetInstance().UpdateComponent();
		ComponentManager<AudioComponent>::GetInstance().UpdateComponent();

		Camera::GetInstance().Update();
		ComponentManager<GraphicsComponent>::GetInstance().UpdateComponent();
	}
}

void GameStateManager::Exit()
{
	if (curState_)
	{
		curState_->Exit();
		delete curState_;
	}
}

void GameStateManager::ChangeState(State* newState)
{
	//if (preState_)
	//	delete preState_;

	preState_ = curState_;
	//Exit();

	curState_ = newState;
	//Init();
}

bool GameStateManager::ShouldExit()
{
	return curState_ == nullptr;
}
