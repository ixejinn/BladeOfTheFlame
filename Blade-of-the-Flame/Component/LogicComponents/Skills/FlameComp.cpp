#include "FlameComp.h"

FlameComp::FlameComp(GameObject* owner) : BaseAttack(owner)
{
	owner_->AddComponent<Transform>();
	owner_->AddComponent<RigidBody>();
	owner_->AddComponent<Sprite>();
	owner->AddComponent<AnimationComp>();
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/1.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/2.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/3.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/4.png", "Attack");
}

void FlameComp::Update()
{
	RigidBody* Rigd = owner_->GetComponent<RigidBody>();
	Rigd->AddVelocity(unitDir * FlameSpeed_);
}

void FlameComp::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void FlameComp::FireFlame()
{
	Transform* Trans = owner_->GetComponent<Transform>();
	RigidBody* Rigd = owner_->GetComponent<RigidBody>();

	AEVec2Normalize(&unitDir, &dir);

	Rigd->AddVelocity(unitDir * FlameSpeed_);
}

ComponentSerializer* FlameComp::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<FlameComp>())
		std::cout << "FlameComp::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<FlameComp>();
}

void FlameComp::LoadFromJson(const json&)
{
}

json FlameComp::SaveToJson()
{
	return json();
}
