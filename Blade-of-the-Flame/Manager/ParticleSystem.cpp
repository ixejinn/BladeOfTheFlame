#include "ParticleSystem.h"
#include "../Component/LogicComponents/Particle.h"
ParticleSystem* ParticleSystem::ptr = nullptr;

ParticleSystem::~ParticleSystem()
{
	for (auto& p : container)
	{
		for (auto& it : p.second)
		{
			delete it;
		}
		p.second.clear();
	}
	container.clear();
}

void ParticleSystem::Update(GameObject* owner)
{
	auto it = container.find(owner);
	for (GameObject* p : it->second)
	{
		if (p->GetComponent<Particle>()->GetLifetime() < 0)
		{
			p->GetComponent<TransformComp>()->SetPos({ owner->GetComponent<TransformComp>()->GetPos() });
			p->GetComponent<RigidbodyComp>()->SetVeolcity({ -owner->GetComponent<RigidbodyComp>()->getVelocity().x/5
				* p->GetComponent<ParticleComp>()->GetInitialVeolcity().x,
				-owner->GetComponent<RigidbodyComp>()->getVelocity().y/5
				* p->GetComponent<ParticleComp>()->GetInitialVeolcity().y });
			p->GetComponent<ParticleComp>()->SetParticleLifetime(1000);
		}
	}
}

void ParticleSystem::SetParticleCount(int count, GameObject* go)
{
	container.emplace(go, NULL);
	auto it = container.find(go);
	for (GameObject* p : it->second)
	{
		delete p;
	}
	it->second.clear();

	for (int i = 0; i < count; i++)
	{
		GameObject* p = GameObjectManager::getPtr()->addObj();
		TransformComp* particletransformcomp = static_cast<TransformComp*>(TransformComp::CreateTransformComp());
		SpriteComp* particlespritecomp = static_cast<SpriteComp*>(SpriteComp::CreateSpriteComp());
		AudioComp* particleaudiocomp = static_cast<AudioComp*>(AudioComp::CreateAudioComp());
		RigidbodyComp* particlerigidbodycomp = static_cast<RigidbodyComp*>(RigidbodyComp::CreateRigidbodyComp());
		ParticleComp* particle = static_cast<ParticleComp*>(ParticleComp::CreateParticleComp());

		p->addComp(particle);
		p->addComp(particletransformcomp);
		p->addComp(particlespritecomp);
		p->addComp(particleaudiocomp);
		p->addComp(particlerigidbodycomp);
		p->checkComp<TransformComp>()->SetPos(go->GetComponent<TransformComp>()->GetPos());
		it->second.push_back(p);
	}
}

void ParticleSystem::SetInitialVelocity(const AEVec2& vel, GameObject* go)
{
	auto it = container.find(go);
	for (GameObject* p : it->second)
	{
		p->GetComponent<ParticleComp>()->SetInitialVelocity(vel);
	}
}

void ParticleSystem::SetInitialScale(const AEVec2& scale, GameObject* go)
{
	auto it = container.find(go);
	for (GameObject* p : it->second)
	{
		p->GetComponent<ParticleComp>()->SetInitialScale(scale);
	}
}

float ParticleSystem::GetLifetime(GameObject* go)
{
	auto it = container.find(go);
	float temp;
	for (GameObject* p : it->second)
	{
		temp = p->GetComponent<ParticleComp>()->GetLifetime();
	}
	return temp;
}

void ParticleSystem::SetLifeTime(float time, GameObject* go)
{
	auto it = container.find(go);
	for (GameObject* p : it->second)
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
