#pragma once
#include <deque>
#include <string>

class GameObject;
class Transform;

class EnvironmentManager
{
private:
	// 3x3
	std::deque<Transform*> up_;
	std::deque<Transform*> center_;
	std::deque<Transform*> down_;

	GameObject* bgm_ = nullptr;

	std::string textureName = "Assets/Realmap.png";
	float zoom_ = 9.f;

	Transform* playerTrans_ = nullptr;

	EnvironmentManager();
	~EnvironmentManager() = default;

	EnvironmentManager(const EnvironmentManager&) = delete;
	EnvironmentManager& operator =(const EnvironmentManager&) = delete;
	EnvironmentManager(EnvironmentManager&&) = delete;
	EnvironmentManager& operator =(EnvironmentManager&&) = delete;

public:
	static EnvironmentManager& GetInstance()
	{
		static EnvironmentManager instance;
		return instance;
	}

	void SetEnvironment();
	void SetPlayerTransform();

	void Update();
};