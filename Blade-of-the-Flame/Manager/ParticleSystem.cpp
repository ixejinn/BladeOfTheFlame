#include "ParticleSystem.h"
#include "../Component/particleComp.h"
#include "../Component/Transform.h"
#include "../Component/Sprite.h"
#include "../Component/Audio.h"

ParticleSystem* ParticleSystem::ptr = nullptr;

ParticleSystem::~ParticleSystem()
{
	for (GameObject* p : allParticle)
	{
		delete p;
	}
	allParticle.clear();
}

void ParticleSystem::Update(GameObject* owner)
{
	for (GameObject* p : allParticle)
	{
		if (p->GetComponent<ParticleComp>()->GetLifetime() < 0)
		{
			p->GetComponent<Transform>()->SetPosition({ owner->GetComponent<Transform>()->GetPosition() });
			p->GetComponent<RigidBody>()->SetVeolcity({ owner->GetComponent<RigidBody>()->GetVelocity() });
			p->GetComponent<ParticleComp>()->SetParticleLifetime(1000);
		}
	}
}

void ParticleSystem::SetParticleCount(int count)
{
	for (GameObject* p : allParticle)
	{
		delete p;
	}
	allParticle.clear();

	for (int i = 0; i < count; i++)
	{
		GameObject* p = GameObjectManager::GetInstance().CreateObject();

		p->AddComponent<Transform>();
		p->AddComponent<Sprite>();
		p->AddComponent<Audio>();
		p->AddComponent<RigidBody>();
		p->AddComponent<ParticleComp>();

		allParticle.push_back(p);
	}
}

void ParticleSystem::SetInitialVelocity(const AEVec2& vel)
{
	for (GameObject* p : allParticle)
	{
		p->GetComponent<ParticleComp>()->SetInitialVelocity(vel);
	}
}

void ParticleSystem::SetInitialScale(const AEVec2& scale)
{
	for (GameObject* p : allParticle)
	{
		p->GetComponent<ParticleComp>()->SetInitialScale(scale);
	}
}

float ParticleSystem::GetLifetime()
{
	float temp;
	for (GameObject* p : allParticle)
	{
		temp = p->GetComponent<ParticleComp>()->GetLifetime();
	}
	return temp;
}

void ParticleSystem::SetLifeTime(float time)
{
	for (GameObject* p : allParticle)
	{
		p->GetComponent<ParticleComp>()->SetParticleLifetime(time);
	}
}

ParticleSystem* ParticleSystem::getPtr()
{
	if (ptr == nullptr)
		ptr = new ParticleSystem;
	return ptr;
}

void ParticleSystem::Delete()
{
	if (ptr != nullptr)
		delete ptr;
	ptr = nullptr;
}
