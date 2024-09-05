#include "Particle.h"
#include "../../Manager/GameObjectManager.h"

Particle::Particle(GameObject* owner) : LogicComponent(owner)
{
	owner_->AddComponent<Transform>();
	owner_->AddComponent<RigidBody>();
	owner_->AddComponent<Sprite>();
	owner_->GetComponent<Sprite>()->SetColor({ 255, 255, 255 });
	state = set;
	owner->active_ = false;
	//mode = Default;

	temp = particleLifetime;
}

void Particle::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void Particle::Update()
{
	if (state == set)
	{
		////투사체 모드
		//if (mode == bullet && followTo != nullptr)
		//{
		//	initialVelocity = followTo->GetComponent<RigidBody>()->GetVelocity()* (-1);
		//	state = go;
		//}
		////레벨업 모드
		//else if (mode == levelup&& followTo != nullptr)
		//{
		//	initialVelocity = followTo->GetComponent<RigidBody>()->GetVelocity() * (-1);
		//	state = go;
		//}
		
		/***for levelupMode***/
		//dtemp = delay;
	}
	if (state == go)
	{
		//if (mode == bullet)
		//{
		
		//}
		//else if (mode == levelup)
		//{

		//}
		

		/***for levelupMode***/
		float dt = AEFrameRateControllerGetFrameRate();
		temp -= dt;
		if (temp > 0)
		{
			AEVec2 temp1234;
			AEVec2Normalize(&temp1234, &initialVelocity);
			owner_->GetComponent<RigidBody>()->AddVelocity({ -dt * (temp1234).x * 2, -dt * (temp1234).y * 2 });
			owner_->GetComponent<Transform>()->SetScale
			({ owner_->GetComponent<Transform>()->GetScale().x ,
				owner_->GetComponent<Transform>()->GetScale().y });
		}
		else
		{
			owner_->GetComponent<RigidBody>()->SetVelocity(initialVelocity);
			owner_->GetComponent<Transform>()->SetScale(initialScale);
			owner_->GetComponent<Transform>()->SetPosition(initialPos);
			//dtemp -= dt;
			//if (dtemp <= 0)
			//{
			//	temp = particleLifetime;
			//	dtemp = delay;
			//}
			state = set;
			owner_->active_ = false;
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
