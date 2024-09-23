#pragma once
#include <list>
#include "GameObjectManager.h"
#include "../Component/LogicComponents/Particle.h"

class ParticleSystem
{
	float radius = 10;
	float speed = 10;
	static ParticleSystem* ptr;
	std::list<GameObject*> container;
	ParticleSystem();
	ParticleSystem(const ParticleSystem&) = delete;
	const ParticleSystem& operator=(const ParticleSystem&) = delete;
	GameObject* player_;
	~ParticleSystem();
public:
	void Update();
	void SetParticle(int count, AEVec2 scale_, float timeL);
	static ParticleSystem* getPtr();
	static void Delete();
};