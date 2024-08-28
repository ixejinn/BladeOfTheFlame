#pragma once
#include <vector>
#include <queue>
#include "AEVec2.h"

class Collider;

class CollisionManager
{
private:
	std::vector<Collider*> colliders_;

	std::queue<std::pair<int, int>> collisionPairs_;

	CollisionManager() = default;
	~CollisionManager() = default;

	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator =(const CollisionManager&) = delete;
	CollisionManager(CollisionManager&&) = delete;
	CollisionManager& operator =(CollisionManager&&) = delete;

public:
	static CollisionManager& GetInstance()
	{
		static CollisionManager instance;
		return instance;
	}

	void AddCollider(Collider* col);
	void DeleteCollider(Collider* col);

	void CheckAllCollision();

	// 같은 GameObject 내의 Collider는 서로 충돌을 검사하지 않음
	// 현재 AABB - Circle의 경우만 collisionPoint 설정
	bool CheckCollision(Collider* colA, Collider* colB, AEVec2& collisionPoint);

	void Clear();
};