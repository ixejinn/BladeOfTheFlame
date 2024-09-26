#pragma once
#include <memory>

class State;

class BossStateManager
{
private:

    enum _BossState
    {
        _currentState,
        _Phase1,
        _Phase2,
        _Phase3
    };

    BossStateManager();
    ~BossStateManager() = default;

    BossStateManager(const BossStateManager&) = delete;
    BossStateManager& operator = (const BossStateManager&) = delete;
    BossStateManager(BossStateManager&&) = delete;
    BossStateManager& operator = (BossStateManager&&) = delete;

    State* preState_;
    State* curState_;

public:
    static BossStateManager& GetInstance()
    {
        static BossStateManager instance;
        return instance;
    }

    void Clear();
    void Init();
    void Update();
    void Exit();

    void ChangeState(State* newState);
    bool ShouldExit();
};