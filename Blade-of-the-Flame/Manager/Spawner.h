#pragma once
#include <stack>
#include <chrono>
#include <string>
#include "AEVec2.h"
#include "GameObjectManager.h"
#include "../Utils/RandomEngine.h"
#include "../Utils/Utils.h"

/**
* @tparam T	NormalMonster, ExpItem, ...
*/
template <typename T>
class Spawner
{
private:
	std::stack<GameObject*> pool_;

	int activeNum_ = 0;
	int maxActiveNum_ = 0;
	int maxNum_ = 0;

	std::chrono::system_clock::time_point timeStart_;
	double spawnPeriod_ = 0.0;
	int spawnNumPerWave_ = 0;

	Transform* playerTrans_ = nullptr;

public:
	Spawner();
	~Spawner();
	
	void Initialize(int maxNum, int maxActiveNum, double spawnPeriod, int spawnNumPerWave);

	void Spawn();
	T* Spawn(const AEVec2& pos);
	void Release(GameObject* obj);

	void Clear();

	int GetActiveNum() const { return activeNum_; }
	int GetMaxActiveNum() const { return maxActiveNum_; }

	void SetMaxActiveNum(int maxActiveNum) { maxActiveNum_ = maxActiveNum; }
};

namespace Manager
{
	extern GameObjectManager& objMgr;
}

template<typename T>
inline Spawner<T>::Spawner() : pool_(), timeStart_()
{
}

template<typename T>
inline Spawner<T>::~Spawner()
{
	Clear();
}

template<typename T>
inline void Spawner<T>::Initialize(int maxNum, int maxActiveNum, double spawnPeriod, int spawnNumPerWave)
{
	maxNum_ = maxNum;
	maxActiveNum_ = maxNum;
	spawnPeriod_ = spawnPeriod;
	spawnNumPerWave_ = spawnNumPerWave;

	for (int i = 0; i < maxNum_; i++)
	{
		GameObject* obj = Manager::objMgr.CreateObject(T::TypeName + std::to_string(i));
		obj->AddComponent<T>();
		obj->active_ = false;
		pool_.push(obj);
	}

	timeStart_ = std::chrono::system_clock::now();
}

template<typename T>
inline void Spawner<T>::Spawn()
{
	if (activeNum_ >= maxActiveNum_ )
		return;

	static bool first = true;
	std::chrono::duration<double> dt = std::chrono::system_clock::now() - timeStart_;
	if (dt.count() < spawnPeriod_  && !first)
		return;
	timeStart_ = std::chrono::system_clock::now();
	first = false;

	static int halfWidth = windowWidth / 2;
	static int halfHeight = windowHeight / 2;

	static auto& engine = RandomEngine::GetInstance().GetEngine();
	static std::uniform_int_distribution<int> spawnZone_{ 0, 3 };
	static std::uniform_int_distribution<int> spawnX_{ halfWidth, halfWidth };
	static std::uniform_int_distribution<int> spawnY_{ -halfHeight, halfHeight };

	for (int i = 0; i < spawnNumPerWave_; i++)
	{
		if (pool_.empty())
			return;

		GameObject* obj = pool_.top();
		pool_.pop();
		activeNum_++;

		int zone = spawnZone_(engine);
		int x = spawnX_(engine);
		int y = spawnY_(engine);

		switch (zone)
		{
		case Direction::LEFT:
			if (x > 0)
				x *= -1;
			x -= halfWidth;
			break;

		case Direction::RIGHT:
			if (x < 0)
				x *= -1;
			x += halfWidth;
			break;

		case Direction::UP:
			if (y < 0)
				y *= -1;
			y += halfHeight;
			break;

		case Direction::DOWN:
			if (y > 0)
				y *= -1;
			y -= halfHeight;
			break;
		}

		if (!playerTrans_)
			playerTrans_ = Manager::objMgr.GetObjectA("player")->GetComponent<Transform>();
		AEVec2 playerPos = playerTrans_->GetPosition();

		obj->GetComponent<Transform>()->SetPosition(x + playerPos.x, y + playerPos.y);
		obj->active_ = true;
	}
}

template<typename T>
inline T* Spawner<T>::Spawn(const AEVec2& pos)
{
	if (pool_.empty())
	{
		std::cout << "ExpItemManager::Spawn() Empty pool" << std::endl;
		return nullptr;
	}

	GameObject* obj = pool_.top();
	pool_.pop();
	activeNum_++;

	obj->GetComponent<Transform>()->SetPosition(pos);
	obj->active_ = true;

	obj->GetComponent<BoxCollider>()->Update();

	return obj->GetComponent<T>();
}

template<typename T>
inline void Spawner<T>::Release(GameObject* obj)
{
	obj->GetComponent<RigidBody>()->ClearVelocity();
	obj->active_ = false;
	pool_.push(obj);
	activeNum_--;
}

template<typename T>
inline void Spawner<T>::Clear()
{
	while (!pool_.empty())
		pool_.pop();
}