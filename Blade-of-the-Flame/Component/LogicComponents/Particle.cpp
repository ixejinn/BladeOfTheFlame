#include "Particle.h"

Particle::Particle(GameObject* owner) : LogicComponent(owner)
{
	owner_->AddComponent<Transform>();
	owner_->AddComponent<RigidBody>();
	owner_->AddComponent<Sprite>();
	owner_->GetComponent<Transform>()->SetScale(initialScale);
	state = set;
	mode = Default;
}
namespace
{
	AEVec2 convert(AEVec2 a)
	{
		AEVec2 worldPos;
		worldPos.x = a.x - windowWidth / 2;
		worldPos.y = -a.y + windowHeight / 2;
		AEVec2 pos;
		AEGfxGetCamPosition(&pos.x, &pos.y);
		AEVec2 result;
		result.x = worldPos.x + pos.x;
		result.y = worldPos.y + pos.y;
		return result;
	}
}
void Particle::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void Particle::Update()
{
	if (state == set)
	{
		//투사체 모드
		if (mode == bullet && followTo != nullptr)
		{
			initialVelocity = followTo->GetComponent<RigidBody>()->GetVelocity()* (-1);
			state = go;
		}
		//레벨업 모드
		else if (mode == levelup&& followTo != nullptr)
		{
			initialVelocity = followTo->GetComponent<RigidBody>()->GetVelocity() * (-1);
			state = go;
		}
	}
	if (state == go)
	{
		if (mode == bullet)
		{

		}
		else if (mode == levelup)
		{

		}
	}
}

void Particle::LoadFromJson(const json&)
{
}

json Particle::SaveToJson()
{
	return json();
}

ComponentSerializer* Particle::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Particle>())
		std::cout << "Particle::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Particle>();
}
