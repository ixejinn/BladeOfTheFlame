#pragma once
#include <string>

class StateSerializer
{
private:
	StateSerializer() = default;
	~StateSerializer() = default;

	StateSerializer(const StateSerializer&) = delete;
	StateSerializer& operator =(const StateSerializer&) = delete;
	StateSerializer(StateSerializer&&) = delete;
	StateSerializer& operator =(StateSerializer&&) = delete;

public:
	static StateSerializer& GetInstance()
	{
		static StateSerializer instance;
		return instance;
	}

	void LoadState(const std::string& filename);
	void SaveState(const std::string& filename);
};