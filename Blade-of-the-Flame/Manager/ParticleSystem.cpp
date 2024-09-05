#include "ParticleSystem.h"
#include <cmath>
#include "../Component/LogicComponents/Particle.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

ParticleSystem* ParticleSystem::ptr = nullptr;

ParticleSystem::ParticleSystem()
{
	player_ = GameObjectManager::GetInstance().GetObjectA("player");
	radius = 10;
	speed = 10;
}

ParticleSystem::~ParticleSystem()
{
	for (auto& p : container)
	{
		delete p;
	}
	container.clear();
}

void ParticleSystem::Update()
{
	int i = 0;
	float angleIncrement = 2 * M_PI / container.size();
	for (GameObject* p : container)
	{
		p->GetComponent<Particle>()->temp= p->GetComponent<Particle>()->particleLifetime;
		p->GetComponent<RigidBody>()->SetVelocity(p->GetComponent<Particle>()->initialVelocity);
		p->GetComponent<Transform>()->SetScale(p->GetComponent<Particle>()->initialScale);
		float angle = i * angleIncrement;
		p->GetComponent<Particle>()->initialPos =
		{ player_->GetComponent<Transform>()->GetPosition().x + radius * cosf(angle),
				player_->GetComponent<Transform>()->GetPosition().y + radius * sinf(angle) };

		p->GetComponent<Transform>()->SetPosition
		({ player_->GetComponent<Transform>()->GetPosition().x + radius * cosf(angle),
				player_->GetComponent<Transform>()->GetPosition().y + radius * sinf(angle) });
		p->active_ = true;
		p->GetComponent<Particle>()->state = go;
		i++;
	}
}

void ParticleSystem::SetParticle(int count, AEVec2 scale, float time)
{
	for (GameObject* p : container)
	{
		delete p;
	}
	container.clear();
	float angleIncrement = 2 * M_PI / count;
	for (int i = 0; i < count; i++)
	{
		GameObject* p = GameObjectManager::GetInstance().CreateObject("Particle" + std::to_string(i));
		p->AddComponent<Particle>();

		p->GetComponent<Particle>()->initialScale = scale;
		p->GetComponent<Particle>()->particleLifetime = time;

		float angle = i * angleIncrement;

		p->GetComponent<Particle>()->initialVelocity =
		{ -speed * sinf(angle), speed * cosf(angle) };

		container.push_back(p);
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


























//#include "ParticleSystem.h"
//#include "../Component/LogicComponents/Particle.h"
//ParticleSystem* ParticleSystem::ptr = nullptr;
//
//ParticleSystem::~ParticleSystem()
//{
//	for (auto& p : container)
//	{
//		for (auto& it : p.second)
//		{
//			delete it;
//		}
//		p.second.clear();
//	}
//	container.clear();
//}
//
//void ParticleSystem::Update(GameObject* owner)
//{
//	//auto it = container.find(owner);
//	//for (GameObject* p : it->second)
//	//{
//	//	if (p->GetComponent<Particle>()->GetLifetime() < 0)
//	//	{
//	//		p->GetComponent<Transform>()->SetPosition({ owner->GetComponent<Transform>()->GetPosition() });
//	//		p->GetComponent<RigidBody>()->SetVelocity({ -owner->GetComponent<RigidBody>()->GetVelocity().x/5
//	//			* p->GetComponent<Particle>()->initialVelocity.x,
//	//			-owner->GetComponent<RigidBody>()->GetVelocity().y/5
//	//			* p->GetComponent<Particle>()->initialVelocity.y });
//	//		p->GetComponent<Particle>()->particleLifetime = 1000;
//	//	}
//	//}
//
//}
//
//void ParticleSystem::SetParticleCount(int count, GameObject* go)
//{
//	container.emplace(go, NULL);
//	auto it = container.find(go);
//	for (GameObject* p : it->second)
//	{
//		delete p;
//	}
//	it->second.clear();
//
//	for (int i = 0; i < count; i++)
//	{
//		GameObject* p = GameObjectManager::GetInstance().CreateObject("Particle" + std::to_string(i));
//		p->AddComponent<Particle>();
//		p->GetComponent<Transform>()->SetPosition(go->GetComponent<Transform>()->GetPosition());
//		it->second.push_back(p);
//	}
//}
//
//void ParticleSystem::SetInitialVelocity(const AEVec2& vel, GameObject* go)
//{
//	auto it = container.find(go);
//	for (GameObject* p : it->second)
//	{
//		p->GetComponent<Particle>()->initialVelocity = vel;
//	}
//}
//
//void ParticleSystem::SetInitialScale(const AEVec2& scale, GameObject* go)
//{
//	auto it = container.find(go);
//	for (GameObject* p : it->second)
//	{
//		p->GetComponent<Particle>()->initialScale = scale;
//	}
//}
//
//float ParticleSystem::GetLifetime(GameObject* go)
//{
//	auto it = container.find(go);
//	float temp;
//	for (GameObject* p : it->second)
//	{
//		temp = p->GetComponent<Particle>()->particleLifetime;
//	}
//	return temp;
//}
//
//void ParticleSystem::SetLifeTime(float time, GameObject* go)
//{
//	auto it = container.find(go);
//	for (GameObject* p : it->second)
//	{
//		p->GetComponent<Particle>()->particleLifetime = time;
//	}
//}
//
//ParticleSystem* ParticleSystem::getPtr()
//{
//	if (ptr == nullptr)
//		ptr = new ParticleSystem;
//	return ptr;
//}
//
//void ParticleSystem::Delete()
//{
//	if (ptr != nullptr)
//		delete ptr;
//	ptr = nullptr;
//}
