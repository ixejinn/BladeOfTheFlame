#include "RigidBody.h"

#include "Transform.h"
#include "../GameObject/GameObject.h"

RigidBody::RigidBody(GameObject* owner) : EngineComponent(owner), velocity_(), preVelocity_(), maxVelocity_(), acceleration_()
{
	velocity_.x = 1;
	velocity_.y = 1;

	preVelocity_.x = 0;
	preVelocity_.y = 0;

	maxVelocity_.x = 10000;
	maxVelocity_.y = 10000;

	acceleration_.x = 0;
	acceleration_.y = 0;
}

bool RigidBody::CheckEpsilon(float val, float EP)
{
	if (val <= -EP || val > EP)
		return true;
	return false;
}

void RigidBody::RemoveFromManager()
{
	ComponentManager<EngineComponent>::GetInstance().DeleteComponent(static_cast<EngineComponent*>(this));
}

void RigidBody::Update()
{
	Transform* trans = owner_->GetComponent<Transform>();
	if (!trans)
	{
		std::cerr << "[ERROR] RigidBody::Update() GameObject " << owner_->GetName() << " does not have Transform" << std::endl;
		return;
	}

	f32 dt = f32(AEFrameRateControllerGetFrameTime());

	acceleration_.x = (velocity_.x - preVelocity_.x) / dt;
	acceleration_.y = (velocity_.y - preVelocity_.y) / dt;

	preVelocity_.x = velocity_.x;
	preVelocity_.y = velocity_.y;

	// linear drag
	velocity_.x *= (1.0f - dragCoefficient_ * dt);
	velocity_.y *= (1.0f - dragCoefficient_ * dt);

	float x = trans->GetPosition().x + velocity_.x * dt + 0.5f * acceleration_.x * dt * dt;
	float y = trans->GetPosition().y + velocity_.y * dt + 0.5f * acceleration_.y * dt * dt;

	trans->SetPosition({ x, y });

	if (!CheckEpsilon(velocity_.x))
		velocity_.x = 0;
	if (!CheckEpsilon(velocity_.y))
		velocity_.y = 0;
}

void RigidBody::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("velocity");
		velocity_.x = it->begin().value();
		velocity_.y = (it->begin() + 1).value();

		it = compData->find("preVelocity");
		preVelocity_.x = it->begin().value();
		preVelocity_.y = (it->begin() + 1).value();

		it = compData->find("maxVelocity");
		maxVelocity_.x = it->begin().value();
		maxVelocity_.y = (it->begin() + 1).value();

		it = compData->find("acceleration");
		acceleration_.x = it->begin().value();
		acceleration_.y = (it->begin() + 1).value();

		it = compData->find("dragCoefficient");
		dragCoefficient_ = it.value();
	}
}

json RigidBody::SaveToJson()
{
	json data, compData;
	data["type"] = TypeName;

	compData["velocity"] = { velocity_.x, velocity_.y };
	compData["preVelocity"] = { preVelocity_.x, preVelocity_.y };
	compData["maxVelocity"] = { maxVelocity_.x, maxVelocity_.y };
	compData["acceleration"] = { acceleration_.x, acceleration_.y };
	compData["dragCoefficient"] = dragCoefficient_;
	
	data["compData"] = compData;
	return data;
}

void RigidBody::AddVelocity(const AEVec2& other)
{
	velocity_.x += other.x;
	velocity_.y += other.y;

	
	velocity_.x = AEClamp(velocity_.x, -maxVelocity_.x, maxVelocity_.x);
	velocity_.y = AEClamp(velocity_.y, -maxVelocity_.y, maxVelocity_.y);
}

void RigidBody::AddVelocity(float x, float y)
{
	velocity_.x += x;
	velocity_.y += y;

	velocity_.x = AEClamp(velocity_.x, -maxVelocity_.x, maxVelocity_.x);
	velocity_.y = AEClamp(velocity_.y, -maxVelocity_.y, maxVelocity_.y);
}

void RigidBody::ClearVelocity()
{
	preVelocity_.x = 0;
	preVelocity_.y = 0;

	velocity_.x = 0;
	velocity_.y = 0;
}

ComponentSerializer* RigidBody::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<RigidBody>())
		std::cout << "RigidBody::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<RigidBody>();
}
