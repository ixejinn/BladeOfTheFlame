#include "CollisionManager.h"

#include <cmath>
#include <memory>
#include "EventManager.h"
#include "../Component/Collider.h"
#include "../GameObject/GameObject.h"
#include "../Event/Event.h"

bool CollisionManager::CheckCircleCircle(CircleCollider* circleA, CircleCollider* circleB)
{
	Transform* transA = circleA->trans_;
	Transform* transB = circleB->trans_;

	AEVec2 centerColA = transA->GetPosition() + circleA->center_;
	AEVec2 centerColB = transB->GetPosition() + circleB->center_;

	float distCenter = std::sqrt((centerColA.x - centerColB.x) * (centerColA.x - centerColB.x) + (centerColA.y - centerColB.y) * (centerColA.y - centerColB.y));

	if (distCenter <= circleA->radius_ + circleB->radius_)
		return true;
	else
		return false;
}

bool CollisionManager::CheckCircleAABB(CircleCollider* circle, BoxCollider* aabb)
{
	Transform* transA = circle->trans_;
	Transform* transB = aabb->trans_;

	AEVec2 centerCircleCol = transA->GetPosition() + circle->center_;
	AEVec2 centerBoxCol = transB->GetPosition() + aabb->center_;

	AEVec2 rangeBoxCol[2] = { aabb->GetBottomLeft(), aabb->GetTopRight() };

	if ((centerCircleCol.x >= rangeBoxCol[0].x && centerCircleCol.x <= rangeBoxCol[1].x) ||
		(centerCircleCol.y >= rangeBoxCol[0].y && centerCircleCol.y <= rangeBoxCol[1].y))
	{
		// Circle collider의 반지름 만큼 box collider를 확장시켰을 때
		// Circle collider의 center가 box collider의 내부에 위치하면 충돌 O
		rangeBoxCol[0].x -= circle->radius_;
		rangeBoxCol[0].y -= circle->radius_;
		rangeBoxCol[1].x += circle->radius_;
		rangeBoxCol[1].y += circle->radius_;

		if (centerCircleCol.x >= rangeBoxCol[0].x &&
			centerCircleCol.x <= rangeBoxCol[1].x &&
			centerCircleCol.y >= rangeBoxCol[0].y &&
			centerCircleCol.y <= rangeBoxCol[1].y)
			return true;
	}
	else {
		// (예외) box collider vertex가 circle collider에 닿지 않는 경우
		AEVec2 verticesBoxCol[4] = {
			{ aabb->GetBottomLeft().x, aabb->GetTopRight().y   },
			{ aabb->GetTopRight().x  , aabb->GetTopRight().y   },
			{ aabb->GetBottomLeft().x, aabb->GetBottomLeft().y },
			{ aabb->GetTopRight().x  , aabb->GetBottomLeft().y }
		};

		for (int i = 0; i < 4; i++)
		{
			// 원의 방정식 사용
			if ((verticesBoxCol[i].x - centerCircleCol.x) * (verticesBoxCol[i].x - centerCircleCol.x) + (verticesBoxCol[i].y - centerCircleCol.y) * (verticesBoxCol[i].y - centerCircleCol.y) <= circle->radius_ * circle->radius_)
				return true;
		}
	}

	return false;
}

bool CollisionManager::CheckCircleOBB(CircleCollider* colA, BoxCollider* colB)
{
	//// TODO

	return false;
}

bool CollisionManager::CheckAABBAABB(Collider* aabbA, Collider* aabbB)
{
	AEVec2 rangeColA[2] = { aabbA->GetBottomLeft(), aabbA->GetTopRight() };
	AEVec2 rangeColB[2] = { aabbB->GetBottomLeft(), aabbB->GetTopRight() };

	if (rangeColA[1].x > rangeColB[0].x &&
		rangeColB[1].x > rangeColA[0].x &&
		rangeColA[1].y > rangeColB[0].y &&
		rangeColB[1].y > rangeColA[0].y)
		return true;
	else
		return false;
}

bool CollisionManager::CheckOBBOBB(BoxCollider* colA, BoxCollider* colB)
{
	f32 minDotProducts[4];

	f32 minDotProduct;
	f32 maxDotProduct;

	// Check colA's normal vector
	for (int i = 0; i < 4; i++)
	{
		int in = i + 1;
		if (in == 4)
			in = 0;

		AEVec2 normal{
			colA->vertices_[in].x - colA->vertices_[i].x,
			colA->vertices_[in].y - colA->vertices_[i].y };

		minDotProduct = FLT_MAX;

		for (const Vec3& vB : colB->vertices_)
		{
			AEVec2 vecAB{
				vB.x - colA->vertices_[in].x, vB.y - colA->vertices_[in].y
			};

			f32 dotProduct = normal.x * vecAB.x + normal.y * vecAB.y;
			if (minDotProduct > dotProduct)
				minDotProduct = dotProduct;
		}

		minDotProducts[in] = minDotProduct;
	}

	maxDotProduct = minDotProducts[0];
	for (int i = 1; i < 4; i++)
	{
		if (maxDotProduct < minDotProducts[i])
			maxDotProduct = minDotProducts[i];
	}

	if (maxDotProduct > 0)
		return false;
	else
		return true;
}

void CollisionManager::AddCollider(Collider* col)
{
	colliders_.push_back(col);
}

void CollisionManager::DeleteCollider(Collider* col)
{
	colliders_.erase(remove(colliders_.begin(), colliders_.end(), col), colliders_.end());
}

void CollisionManager::CheckAllCollision()
{
	for (int i = 0; i < colliders_.size(); i++)
	{
		for (int j = i + 1; j < colliders_.size(); j++)
		{
			if (CheckCollision(colliders_[i], colliders_[j]))
				collisionPairs_.push({ colliders_[i], colliders_[j] });
		}
	}

	while (!collisionPairs_.empty())
	{
		auto pair = collisionPairs_.front();

		CollisionEvent* event1to2 = new CollisionEvent();
		event1to2->from_ = pair.first->owner_;
		pair.first->CallHandler(event1to2);

		CollisionEvent* event2to1 = new CollisionEvent();
		event2to1->from_ = pair.second->owner_;
		pair.second->CallHandler(event2to1);

		collisionPairs_.pop();
	}
}

bool CollisionManager::CheckCollision(Collider* colA, Collider* colB)
{
	bool objActive = colA->owner_->active_ && colB->owner_->active_;				// 활성 오브젝트 확인
	bool checkLayer = layerCollisionMatrix_[colA->GetLayer()][colB->GetLayer()];	// 충돌 레이어 확인
	if (objActive && checkLayer == false)
		return false;

	// 1차 충돌 검사 (AABB - AABB)
	if (!CheckAABBAABB(colA, colB))
		return false;

	if (colA->type_ == Collider::AABB_TYPE && colB->type_ == Collider::AABB_TYPE)
		return true;	// 2차 검사 필요 없음

	// 2차 충돌 검사
	Collider* cA = colA;
	Collider* cB = colB;
	if (cA->type_ > cB->type_)
	{
		Collider* tmp = cA;
		cA = cB;
		cB = tmp;
	}

	Transform* transA = cA->trans_;
	Transform* transB = cB->trans_;

	switch (cA->type_)
	{
	case Collider::CIRCLE_TYPE:
	{
		switch (cB->type_)
		{
		case Collider::CIRCLE_TYPE:
			return CheckCircleCircle(static_cast<CircleCollider*>(cA), static_cast<CircleCollider*>(cB));

		case Collider::AABB_TYPE:
			return CheckCircleAABB(static_cast<CircleCollider*>(cA), static_cast<BoxCollider*>(cB));

		case Collider::OBB_TYPE:
			return CheckCircleOBB(static_cast<CircleCollider*>(cA), static_cast<BoxCollider*>(cB));
			
		default:
			std::cerr << "CollisionManager::CheckCollision() Unknown Collider type" << std::endl;
		}
	}

	case Collider::AABB_TYPE:
		return CheckOBBOBB(static_cast<BoxCollider*>(cA), static_cast<BoxCollider*>(cB)) &&
			CheckOBBOBB(static_cast<BoxCollider*>(cB), static_cast<BoxCollider*>(cA));

	case Collider::OBB_TYPE:
		return CheckOBBOBB(static_cast<BoxCollider*>(cA), static_cast<BoxCollider*>(cB)) &&
			CheckOBBOBB(static_cast<BoxCollider*>(cB), static_cast<BoxCollider*>(cA));
	}

	return false;
}

void CollisionManager::Clear()
{
	colliders_.clear();
}