#include "CollisionManager.h"

#include <cmath>
#include "EventManager.h"
#include "../Component/Collider.h"
#include "../GameObject/GameObject.h"
#include "../Event/Event.h"

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
			AEVec2 collisionPoint;
			if (CheckCollision(colliders_[i], colliders_[j], collisionPoint))
			{
				colliders_[i]->collisionPoint_ = collisionPoint;
				colliders_[j]->collisionPoint_ = collisionPoint;

				collisionPairs_.push({ i, j });
			}
		}
	}

	while (!collisionPairs_.empty())
	{
		auto pair = collisionPairs_.front();

		CollisionEvent* collision1{ new CollisionEvent() };
		collision1->from_ = colliders_[pair.first]->owner_;
		collision1->to_ = colliders_[pair.second]->owner_;
		EventManager::GetInstance().AddEvent(static_cast<BaseEvent*>(collision1));

		CollisionEvent* collision2{ new CollisionEvent() };
		collision2->from_ = colliders_[pair.second]->owner_;
		collision2->to_ = colliders_[pair.first]->owner_;
		EventManager::GetInstance().AddEvent(static_cast<BaseEvent*>(collision2));

		collisionPairs_.pop();
	}
}

bool CollisionManager::CheckCollision(Collider* colA, Collider* colB, AEVec2& collisionPoint)
{
	// 같은 GameObject의 Collider는 충돌 검사 하지 않음
	if (colA->owner_ == colB->owner_)
		return false;

	Transform* transA = colA->owner_->GetComponent<Transform>();
	Transform* transB = colB->owner_->GetComponent<Transform>();

	int type = colA->type_ + colB->type_;
	switch (type)
	{
	case 0:	// Circle - Circle
	{
		CircleCollider* circleColA = static_cast<CircleCollider*>(colA);
		CircleCollider* circleColB = static_cast<CircleCollider*>(colB);

		AEVec2 centerColA = transA->GetPosition() + circleColA->center_;
		AEVec2 centerColB = transB->GetPosition() + circleColB->center_;

		float distCenter = std::sqrt((centerColA.x - centerColB.x) * (centerColA.x - centerColB.x) + (centerColA.y - centerColB.y) * (centerColA.y - centerColB.y));

		if (distCenter <= circleColA->radius_ + circleColB->radius_)
			return true;
		else
			return false;
	}

	case 1:	// AABB - Circle
	{
		CircleCollider* circleCol;
		BoxCollider* boxCol;

		AEVec2 centerCircleCol, centerBoxCol;

		if (colA->type_ == Collider::CIRCLE)
		{
			circleCol = static_cast<CircleCollider*>(colA);
			boxCol = static_cast<BoxCollider*>(colB);

			centerCircleCol = transA->GetPosition() + circleCol->center_;
			centerBoxCol = transB->GetPosition() + boxCol->center_;
		}
		else
		{
			circleCol = static_cast<CircleCollider*>(colB);
			boxCol = static_cast<BoxCollider*>(colA);

			centerCircleCol = transB->GetPosition() + boxCol->center_;
			centerBoxCol = transA->GetPosition() + circleCol->center_;
		}

		AEVec2 rangeBoxCol[2] = { boxCol->GetBottomLeft(), boxCol->GetTopRight() };

		if ((centerCircleCol.x >= rangeBoxCol[0].x && centerCircleCol.x <= rangeBoxCol[1].x) ||
			(centerCircleCol.y >= rangeBoxCol[0].y && centerCircleCol.y <= rangeBoxCol[1].y))
		{
			// Circle collider의 반지름 만큼 box collider를 확장시켰을 때
			// Circle collider의 center가 box collider의 내부에 위치하면 충돌 O
			rangeBoxCol[0].x -= circleCol->radius_;
			rangeBoxCol[0].y -= circleCol->radius_;
			rangeBoxCol[1].x += circleCol->radius_;
			rangeBoxCol[1].y += circleCol->radius_;

			if (centerCircleCol.x >= rangeBoxCol[0].x &&
				centerCircleCol.x <= rangeBoxCol[1].x &&
				centerCircleCol.y >= rangeBoxCol[0].y &&
				centerCircleCol.y <= rangeBoxCol[1].y)
			{
				collisionPoint = centerCircleCol;
				// unitReflDir에 공이 반사될 unit vector 설정
				if (centerCircleCol.x >= boxCol->GetBottomLeft().x && centerCircleCol.x <= boxCol->GetTopRight().x && centerCircleCol.y >= boxCol->GetTopRight().y)
					// Circle collider가 box collider의 위에 위치
					collisionPoint.y -= circleCol->radius_;

				else if (centerCircleCol.x >= boxCol->GetBottomLeft().x && centerCircleCol.x <= boxCol->GetTopRight().x && centerCircleCol.y <= boxCol->GetBottomLeft().y)
					// Circle collider가 box collider의 아래에 위치
					collisionPoint.y += circleCol->radius_;

				else if (centerCircleCol.y >= boxCol->GetBottomLeft().y && centerCircleCol.y <= boxCol->GetTopRight().y && centerCircleCol.x <= boxCol->GetBottomLeft().x)
					// Circle collider가 box collider의 왼쪽에 위치
					collisionPoint.x += circleCol->radius_;

				else
					// Circle collider가 box collider의 오른쪽에 위치
					collisionPoint.x -= circleCol->radius_;

				return true;
			}
		}
		else {
			// (예외) box collider vertex가 circle collider에 닿지 않는 경우
			AEVec2 verticesBoxCol[4] = {
				{ boxCol->GetBottomLeft().x, boxCol->GetTopRight().y },
				{ boxCol->GetTopRight().x, boxCol->GetTopRight().y },
				{ boxCol->GetBottomLeft().x, boxCol->GetBottomLeft().y },
				{ boxCol->GetTopRight().x, boxCol->GetBottomLeft().y}
			};

			for (int i = 0; i < 4; i++)
			{
				// 원의 방정식 사용
				if ((verticesBoxCol[i].x - centerCircleCol.x) * (verticesBoxCol[i].x - centerCircleCol.x) + (verticesBoxCol[i].y - centerCircleCol.y) * (verticesBoxCol[i].y - centerCircleCol.y) <= circleCol->radius_ * circleCol->radius_)
				{
					collisionPoint = verticesBoxCol[i];
					return true;
				}
			}
		}
		
		return false;
	}

	case 2:	// AABB - AABB
	{
		BoxCollider* boxColA = static_cast<BoxCollider*>(colA);
		BoxCollider* boxColB = static_cast<BoxCollider*>(colB);

		AEVec2 rangeColA[2] = { boxColA->GetBottomLeft(), boxColA->GetTopRight() };
		AEVec2 rangeColB[2] = { boxColB->GetBottomLeft(), boxColB->GetTopRight() };

		if (rangeColA[1].x > rangeColB[0].x &&
			rangeColB[1].x > rangeColA[0].x &&
			rangeColA[1].y > rangeColB[0].y &&
			rangeColB[1].y > rangeColA[0].y)
			return true;
		else
			return false;
	}
	}
	return false;
}

void CollisionManager::Clear()
{
	colliders_.clear();
}
