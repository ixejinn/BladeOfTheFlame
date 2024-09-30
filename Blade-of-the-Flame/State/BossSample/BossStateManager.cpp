#include "../State.h"
#include "BossStateManager.h"

BossStateManager::BossStateManager() :preState_(nullptr), curState_(nullptr){}

void BossStateManager::Clear()
{
    preState_ = nullptr;
    curState_ = nullptr;
}

void BossStateManager::Init()
{
    if (curState_)
        curState_->Init();
}

void BossStateManager::Update()
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
    }
}

void BossStateManager::Exit()
{
    if (curState_)
    {
        curState_->Exit();
        delete curState_;
    }
    else
    {
        preState_->Exit();
        delete preState_;
    }
}

void BossStateManager::ChangeState(State* newState)
{
    preState_ = curState_;
    curState_ = newState;
}

bool BossStateManager::ShouldExit()
{
    return curState_ == nullptr;
}
