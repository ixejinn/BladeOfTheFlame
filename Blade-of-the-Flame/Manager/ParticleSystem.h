//#pragma once
//#include <list>
//#include <map>
//#include "GameObjectManager.h"
//#include "../../Component/LogicComponents/Particle.h"
//class ParticleSystem
//{
//	static ParticleSystem* ptr;
//	std::map<GameObject*, std::list<GameObject*>> container;
//
//	ParticleSystem() = default;
//	ParticleSystem(const ParticleSystem&) = delete;
//	const ParticleSystem& operator=(const ParticleSystem&) = delete;
//	~ParticleSystem();
//public:
//	void Update(GameObject* owner);
//	void SetParticleCount(int count, GameObject* go);
//	void SetInitialVelocity(const AEVec2& vel, GameObject* go);
//	void SetInitialScale(const AEVec2& scale, GameObject* go);
//	float GetLifetime(GameObject* go);
//	void SetLifeTime(float time, GameObject* go);
//	static ParticleSystem* getPtr();
//	static void Delete();
//};
#pragma once
#include <list>
#include "GameObjectManager.h"
#include "../../Component/LogicComponents/Particle.h"
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