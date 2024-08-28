#include "Ball.h"

#include "../GameObject/GameObject.h"
#include "../Utils/MathUtils.h"
#include "../Manager/EventManager.h"
#include "../Event/Event.h"

Ball::Ball(GameObject* owner) : LogicComponent(owner), unitReflDir_()
{
	RigidBody* rb = owner_->GetComponent<RigidBody>();
	if (!rb)
	{
		std::cerr << "[ERROR] Ball::Ball() RigidBody not found" << std::endl;
		return;
	}

	Restart();
}

void Ball::Update()
{
	Transform* trans = owner_->GetComponent<Transform>();
	if (!trans)
	{
		std::cerr << "[ERROR] Ball::Restart() Transform not found" << std::endl;
		return;
	}

	AEVec2 position = trans->GetPosition();

	if (position.x <= -Ball::limit.x || position.x >= Ball::limit.x)
	{
		ScoreEvent* event{ new ScoreEvent() };
		event->from_ = owner_;
		if (position.x <= -Ball::limit.x)
			event->scoreTeam = 1;
		else if (position.x >= Ball::limit.x)
			event->scoreTeam = 0;

		EventManager::GetInstance().AddEvent(event);
		Restart();
	}
}

void Ball::LoadFromJson(const json&)
{
}

json Ball::SaveToJson()
{
	return json();
}

void Ball::OnEvent(BaseEvent* event)
{
	std::type_index eventType = std::type_index(typeid(*event));

	if (event->from_ == owner_ && eventType == std::type_index(typeid(CollisionEvent)))
	{
		CollisionEvent* colEvent = dynamic_cast<CollisionEvent*>(event);
		GameObject* partner = colEvent->to_;

		RigidBody* rb = owner_->GetComponent<RigidBody>();
		if (!rb)
		{
			std::cerr << "[ERROR] Ball::OnCollision() RigidBody not found" << std::endl;
			return;
		}

		AEVec2 preVelocity = rb->GetVelocity();
		float preVelocityLen = AEVec2Length(&preVelocity);

		AEVec2 velocity = preVelocity;

		rb->ClearVelocity();

		// Wall과 충돌하는 경우
		if (partner->GetComponent<Wall>())
		{
			velocity.y *= -1.f;

			AEVec2 unitDir;
			AEVec2Normalize(&unitDir, &velocity);

			velocity = unitDir * preVelocityLen * wallSpeedUp;
		}
		// Racket과 충돌하는 경우
		else if (partner->GetComponent<Racket>())
		{
			Racket* racket = partner->GetComponent<Racket>();

			AEVec2 collisionPoint = owner_->GetComponent<CircleCollider>()->GetCollisionPoint();
			AEVec2 racketCenter = partner->GetComponent<Transform>()->GetPosition();

			//// TODO: Racket에 translate center for reflection에 관한 멤버 변수 추가?
			if (collisionPoint.x > racketCenter.x)
				racketCenter.x -= 20.f;
			else
				racketCenter.x += 20.f;

			AEVec2 reflectedDir = collisionPoint - racketCenter;
			AEVec2Normalize(&unitReflDir_, &reflectedDir);

			velocity = unitReflDir_ * preVelocityLen * racketSpeedUp;
		}
		else
		{
			std::cerr << "[ERROR] Ball::OnCollision() Unknown collision target" << std::endl;
			velocity = velocity * -1.f;
		}

		rb->AddVelocity(velocity);
	}
}

void Ball::SetCollisionPoint(const AEVec2& point)
{
	unitReflDir_ = point;
}

void Ball::Restart()
{
	RigidBody* rb = owner_->GetComponent<RigidBody>();
	if (!rb)
	{
		std::cerr << "[ERROR] Ball::Restart() RigidBody not found" << std::endl;
		return;
	}

	Transform* trans = owner_->GetComponent<Transform>();
	if (!trans)
	{
		std::cerr << "[ERROR] Ball::Restart() Transform not found" << std::endl;
		return;
	}

	auto& engine = RandomEngine::GetInstance().GetEngine();

	// 시작 위치 설정
	int rIdx = startYPosIdx_(engine);
	float negative = 1.f;
	if (rIdx < 0)
	{
		rIdx *= -1;
		negative = -1.f;
	}
	trans->SetPosition(0.f, negative * ballStartYPos_[rIdx]);

	// 시작 방향 설정
	rb->ClearVelocity();

	AEVec2 dir{ windowWidth / 2.f, float(startYDir_(engine))};
	AEVec2 unitDir;
	AEVec2Normalize(&unitDir, &dir);

	dir = unitDir * speed_;

	if (startXSign_ == 0)
	{
		if (startXDir_(engine))
			startXSign_ = 1;
		else
			startXSign_ = -1;
	}
	else
		startXSign_ *= -1;
	dir.x *= startXSign_;

	rb->AddVelocity(dir);
}

ComponentSerializer* Ball::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Ball>())
		std::cout << "Wall::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Ball>();
}
