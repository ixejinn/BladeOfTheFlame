#pragma once
#include <list>
#include "../../Manager/GameObjectManager.h"
#include "../Component/particleComp.h"

class ParticleSystem
{
	static ParticleSystem* ptr;
	std::list<GameObject*> allParticle;

	ParticleSystem() = default;
	ParticleSystem(const ParticleSystem&) = delete;
	const ParticleSystem& operator=(const ParticleSystem&) = delete;
	~ParticleSystem();
public:
	void Update(GameObject* owner);
	void SetParticleCount(int count);
	void SetInitialVelocity(const AEVec2& vel);
	void SetInitialScale(const AEVec2& scale);
	float GetLifetime();
	void SetLifeTime(float time);
	static ParticleSystem* getPtr();
	static void Delete();
};