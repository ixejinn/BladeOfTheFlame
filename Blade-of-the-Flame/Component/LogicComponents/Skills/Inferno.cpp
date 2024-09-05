//#include "Inferno.h"
//#include "../../Event/Event.h"
//#include "../../Manager/EventManager.h"
//#include "../../AnimationComp.h"
//#include "../../Manager/SkillManager.h"
//#include <iostream>
//#include "AEUtil.h"
//Inferno::Inferno(GameObject* owner) : BaseAttack(owner)
//{
//	owner->active_ = false;
//	dmg_ = 3;
//	range_ = 700.f;
//	cooldown_ = 0;
//	dmgGrowthRate_ = 10.f;
//	cState = df;
//	owner->AddComponent<Transform>();
//	owner->AddComponent<RigidBody>();
//	owner->AddComponent<Sprite>();
//	owner->GetComponent<AnimationComp>()->SetTerm(200.0f);
//	owner->GetComponent<RigidBody>()->ClearVelocity();
//	owner_->GetComponent<Transform>()->SetScale({ range_, range_ });
//}
//
//void Inferno::Update()
//{
//}
//
//void Inferno::AttackObject()
//{
//}
//
//ComponentSerializer* Inferno::CreateComponent(GameObject* owner)
//{
//	if (!owner->AddComponent<Inferno>())
//		std::cout << "Inferno::CreateComponent() Component already exists" << std::endl;
//
//	return owner->GetComponent<Inferno>();
//}
