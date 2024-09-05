#pragma once
#include <memory>

class State;

/**
* @brief	GameStateManager은 State의 생성과 해제에 관여하지 않음
*/
class GameStateManager
{
private:
	GameStateManager();
	~GameStateManager() = default;

	GameStateManager(const GameStateManager&) = delete;
	GameStateManager& operator =(const GameStateManager&) = delete;
	GameStateManager(GameStateManager&&) = delete;
	GameStateManager& operator =(GameStateManager&&) = delete;

	State* preState_;
	State* curState_;

public:
	static GameStateManager& GetInstance()
	{
		static GameStateManager instance;
		return instance;
	}

	void Clear();

	void Init();
	void Update();
	void Exit();

	void ChangeState(State* newState);

	bool ShouldExit();
};