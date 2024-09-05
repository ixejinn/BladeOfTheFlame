//#include "Flame.h"
//#include "../../Event/Event.h"
//#include "../../Manager/EventManager.h"
//#include "../../AnimationComp.h"
//#include "FlameComp.h"
//#include "../../Manager/SkillManager.h"
//
//Flame::Flame(GameObject* owner) : BaseAttack(owner)
//{
//	owner->active_ = false;
//	dmg_ = 0;
//	range_ = 10;
//	cooldown_ = 0;
//	dmgGrowthRate_ = 10;
//	cState = df;
//	owner_->AddComponent<BoxCollider>();
//	owner->AddComponent<Sprite>();
//	owner->AddComponent<AnimationComp>();
//	owner->GetComponent<RigidBody>()->ClearVelocity();
//	owner_->GetComponent<Transform>()->SetScale({ 50, 50 });
//	BoxCollider* col = owner_->GetComponent<BoxCollider>();
//	col->SetType(Collider::AABB_TYPE);
//	col->SetLayer(Collider::P_ATTACK);
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile001.png", "Idle");
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile002.png", "Idle");
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile003.png", "Idle");
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile005.png", "Idle");
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile006.png", "Idle");
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile007.png", "Idle");
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile008.png", "Idle");
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile009.png", "Idle");
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile010.png", "Idle");
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile011.png", "Idle");
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile012.png", "Idle");
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile013.png", "Idle");
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile014.png", "Idle");
//	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile015.png", "Idle");
//	owner->GetComponent<AnimationComp>()->SetTerm(100.0f);
//}
//
//namespace
//{
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
//
//void Flame::Update()
//{
//	if (!AEInputCheckCurr(AEVK_LBUTTON) && cState == df)
//		cState = ready;
//	if (cState == ready)
//	{
//		owner_->GetComponent<Transform>()->SetScale({ 250, 250 });
//		owner_->GetComponent<AnimationComp>()->ChangeAnimation("Idle");
//		owner_->GetComponent<Transform>()->SetPosition(player_->GetComponent<Transform>()->GetPosition());
//		dmg_ = 0;
//		AEInputInit();
//		s32 x, y;
//		AEInputGetCursorPosition(&x, &y);
//		AEVec2 mousePosF({ static_cast<float>(x), static_cast<float>(y) });
//		convertPos = convert(mousePosF);
//		if (AEInputCheckCurr(AEVK_LBUTTON))
//		{
//			cState = shoot;
//			owner_->GetComponent<AnimationComp>()->ChangeAnimation("Attack");
//			owner_->GetComponent<Transform>()->SetScale({ 50, 50 });
//			AEVec2 attackDir{ convertPos - owner_->GetComponent<Transform>()->GetPosition() };
//			AEVec2Normalize(&unitDir, &attackDir);
//			SkillManager::GetInstance().resetKeys();
//			player_->GetComponent<Player>()->curAttack_ = nullptr;
//
//			CreateFlameObj(unitDir)
//
//		}
//	}
//	else if (cState == shoot)
//	{
//		templifetime -= AEFrameRateControllerGetFrameTime();
//		if (templifetime > 0)
//		{
//			owner_->GetComponent<RigidBody>()->AddVelocity(unitDir * 200);
//			AttackObject();
//		}
//		else
//		{
//			cState = df;
//			SkillManager::GetInstance().CooldownCountFlame = 0;
//
//			owner_->GetComponent<RigidBody>()->ClearVelocity();
//			owner_->active_ = false;
//		}
//	}
//}
//
//GameObject* Flame::CreateFlameObj(float lifeT, float flameD, float flameS, AEVec2 sca, AEVec2 dir)
//{
//	std::string unique_Flame_name = "Flame" + std::to_string(flame.size());
//	GameObject* addflame = GameObjectManager::GetInstance().CreateObject(unique_Flame_name);
//	flame.push_back(addflame);
//	addflame->AddComponent<FlameComp>();
//	addflame->GetComponent<FlameComp>()->SetDir(dir);
//	addflame->GetComponent<FlameComp>()->FlameDmg_ = dmg_;
//	return addflame;
//}
//
//void Flame::LoadFromJson(const json&)
//{
//}
//json Flame::SaveToJson()
//{
//	return json();
//}
//ComponentSerializer* Flame::CreateComponent(GameObject* owner)
//{
//	if (!owner->AddComponent<Flame>())
//		std::cout << "Flame::CreateComponent() Component already exists" << std::endl;
//
//	return owner->GetComponent<Flame>();
//}
