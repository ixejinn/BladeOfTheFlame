//#include "FlameComp.h"
//namespace
//{
//
//	AEVec2 convert(AEVec2 a)
//	{
//		AEVec2 worldPos;
//		worldPos.x = a.x - windowWidth / 2;
//		worldPos.y = -a.y + windowHeight / 2;
//		AEVec2 pos;
//		AEGfxGetCamPosition(&pos.x, &pos.y);
//		AEVec2 result;
//		result.x = worldPos.x + pos.x;
//		result.y = worldPos.y + pos.y;
//		return result;
//	}
//}
//FlameComp::FlameComp(GameObject* owner) : BaseAttack(owner)
//{
//	owner_->AddComponent<Transform>();
//	owner_->AddComponent<RigidBody>();
//	owner_->AddComponent<Sprite>();
//	owner->AddComponent<AnimationComp>();
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/1.png", "Attack");
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/2.png", "Attack");
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/3.png", "Attack");
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/4.png", "Attack");
//}
//
//void FlameComp::Update()
//{
//	RigidBody* Rigd = owner_->GetComponent<RigidBody>();
//	Rigd->AddVelocity(unitDir * FlameSpeed_);
//
//	//fire
//	//Transform* Trans = owner_->GetComponent<Transform>();
//	//RigidBody* Rigd = owner_->GetComponent<RigidBody>();
//
//	//AEVec2Normalize(&unitDir, &dir);
//
//	//Rigd->AddVelocity(unitDir * FlameSpeed_);
//}
//
//void FlameComp::LevelUp()
//{
//	dmg_ += int(dmg_ * dmgGrowthRate_ / 100);
//	lifetime += 1;
//}
//
//void FlameComp::SetDir(AEVec2 diraction)
//{
//	dir = convert(diraction);
//}
//
//void FlameComp::AttackObject()
//{
//}
//
//void FlameComp::RemoveFromManager()
//{
//	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
//}
//
//ComponentSerializer* FlameComp::CreateComponent(GameObject* owner)
//{
//	if (!owner->AddComponent<FlameComp>())
//		std::cout << "FlameComp::CreateComponent() Component already exists" << std::endl;
//
//	return owner->GetComponent<FlameComp>();
//}
//
//void FlameComp::LoadFromJson(const json&)
//{
//}
//
//json FlameComp::SaveToJson()
//{
//	return json();
//}
