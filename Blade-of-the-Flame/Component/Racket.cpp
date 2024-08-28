#include "Racket.h"

#include <typeindex>
#include "../GameObject/GameObject.h"

Racket::Racket(GameObject* owner) : LogicComponent(owner) {}

void Racket::Update()
{
}

void Racket::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");
	if (compData != data.end()) {}
}

json Racket::SaveToJson()
{
	json data, compData;
	data["type"] = TypeName;

	data["compData"] = compData;
	return data;
}

void Racket::OnEvent(BaseEvent* event)
{
	std::type_index eventType = std::type_index(typeid(*event));

	if (event->from_ == owner_ && eventType == std::type_index(typeid(CollisionEvent)))
	{
		CollisionEvent* colEvent = static_cast<CollisionEvent*>(event);
		RigidBody* rb = owner_->GetComponent<RigidBody>();
		if (!rb)
		{
			std::cerr << "[ERROR] Racket::OnCollision() RigidBody not found" << std::endl;
			return;
		}
		rb->ClearVelocity();

		GameObject* target = colEvent->to_;

		if (target->GetComponent<Wall>())
		{
			Transform* trans = owner_->GetComponent<Transform>();
			if (!trans)
			{
				std::cerr << "[ERROR] Racket::OnCollision() Transform not found" << std::endl;
				return;
			}

			AEVec2 pos = trans->GetPosition();
			float y = Wall::position.y - Wall::size.y / 2.f - Racket::size.y / 2.f - 1.f;
			if (pos.y < 0)
				pos.y = -y;
			else
				pos.y = y;
			trans->SetPosition(pos);
		}
	}
}

ComponentSerializer* Racket::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Racket>())
		std::cout << "Racket::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Racket>();
}
