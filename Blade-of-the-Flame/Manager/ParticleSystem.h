#pragma once
#include <list>
#include <map>
#include "GameObjectManager.h"
#include "../../Component/LogicComponents/Particle.h"
class ParticleSystem
{
	static ParticleSystem* ptr;
	std::map<GameObject*, std::list<GameObject*>> container;

	ParticleSystem() = default;
	ParticleSystem(const ParticleSystem&) = delete;
	const ParticleSystem& operator=(const ParticleSystem&) = delete;
	~ParticleSystem();
public:
	void Update(GameObject* owner);
	void SetParticleCount(int count, GameObject* go);
	void SetInitialVelocity(const AEVec2& vel, GameObject* go);
	void SetInitialScale(const AEVec2& scale, GameObject* go);
	float GetLifetime(GameObject* go);
	void SetLifeTime(float time, GameObject* go);
	static ParticleSystem* getPtr();
	static void Delete();
};