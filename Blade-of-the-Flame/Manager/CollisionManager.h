#pragma once
#include <vector>
#include <queue>
#include "AEVec2.h"
#include "../Component/Collider.h"

class CollisionManager
{
private:
	std::vector<Collider*> colliders_;

	std::queue<std::pair<Collider*, Collider*>> collisionPairs_;

	bool layerCollisionMatrix_[LAYER_NUM][LAYER_NUM]{
		//				P_AABB,	P_CIRCLE,	P_ATTACK,	E_BODY,	E_ATTACK,	ITEM,	EXP_ITEM, SEARCH
		/* P_AABB */ {	false,	false,		false,		true,	true,		true,	true, false	},
		/* P_CIRC */ {	false,	false,		false,		false,	false,		false,	true, false	},
		/* P_ATCK */ {  false,	false,		false,		true,	false,		false,	false, false	},
		/* E_BODY */ {  true,	false,		true,		true,	false,		false,	false, true	},
		/* E_ATCK */ {  true,	false,		false,		false,	false,		false,	false, false	},
		/* ITEM   */ {	true,	false,		false,		false,	false,		false,	false, false	},
		/* EXP_IT */ {  true,	true,		false,		false,	false,		false,	false, false	},
		/* SEARCH */ { false,	false,		false,		true,	false,		false,	false, false }
	};

	bool CheckCircleCircle(CircleCollider* colA, CircleCollider* colB);
	bool CheckCircleAABB(CircleCollider* colA, BoxCollider* colB);
	bool CheckCircleOBB(CircleCollider* colA, BoxCollider* colB);
	bool CheckAABBAABB(Collider* colA, Collider* colB);
	bool CheckOBBOBB(BoxCollider* colA, BoxCollider* colB);

	void SetCollisionEvent(CollisionEvent* event, Collider* fromCol);

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
	bool CheckCollision(Collider* colA, Collider* colB);

	void Clear();
};