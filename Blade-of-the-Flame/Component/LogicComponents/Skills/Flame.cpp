#include "Flame.h"

#include "../../../Event/Event.h"
#include "../../../Manager/EventManager.h"
#include "../../AnimationComp.h"
#include "FlameComp.h"
#include "../../../Manager/SkillManager.h"

int Flame::count;

Flame::Flame(GameObject* owner) : BaseAttack(owner)
{
	owner->active_ = false;
	dmg_ = 5;
	range_ = 250;
	cooldown_ = 3;
	dmgGrowthRate_ = 5.f;
	cState = df;
	count = 0;
	owner->AddComponent<Transform>();
	owner->AddComponent<Sprite>();
	owner->AddComponent<RigidBody>();
	owner->AddComponent<AnimationComp>();
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile001.png", "Idle");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile002.png", "Idle");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile003.png", "Idle");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile005.png", "Idle");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile006.png", "Idle");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile007.png", "Idle");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile008.png", "Idle");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile009.png", "Idle");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile010.png", "Idle");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile011.png", "Idle");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile012.png", "Idle");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile013.png", "Idle");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile014.png", "Idle");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/FlameAnime/tile015.png", "Idle");
	owner->GetComponent<AnimationComp>()->SetTerm(100.0f);
	owner->GetComponent<RigidBody>()->ClearVelocity();
	fl = GameObjectManager::GetInstance().CreateObject();
}

namespace
{
	AEVec2 convert(AEVec2 a)
	{
		AEVec2 worldPos;
		worldPos.x = a.x - windowWidth / 2;
		worldPos.y = -a.y + windowHeight / 2;
		AEVec2 pos;
		AEGfxGetCamPosition(&pos.x, &pos.y);
		AEVec2 result;
		result.x = worldPos.x + pos.x;
		result.y = worldPos.y + pos.y;
		return result;
	}
}

void Flame::Update()
{
	if (!AEInputCheckCurr(AEVK_LBUTTON) && cState == df)
		cState = ready;
	if (cState == ready)
	{
		owner_->GetComponent<Transform>()->SetScale({ range_, range_ });
		owner_->GetComponent<AnimationComp>()->ChangeAnimation("Idle");
		owner_->GetComponent<Transform>()->SetPosition(player_->GetComponent<Transform>()->GetPosition());
		AEInputInit();
		s32 x, y;
		AEInputGetCursorPosition(&x, &y);
		AEVec2 mousePosF({ static_cast<float>(x), static_cast<float>(y) });
		convertPos = convert(mousePosF);
		if (AEInputCheckCurr(AEVK_LBUTTON))
		{
			cState = shoot;
			AEVec2 attackDir{ convertPos - owner_->GetComponent<Transform>()->GetPosition() };
			AEVec2Normalize(&unitDir, &attackDir);
		}
	}
	else if (cState == shoot)
	{
		AttackObject();
		cState = df;
		SkillManager::GetInstance().CooldownCountFlame = 0;
		owner_->GetComponent<RigidBody>()->ClearVelocity();
		SkillManager::GetInstance().resetKeys();
		player_->GetComponent<Player>()->curAttack_ = nullptr;
		owner_->active_ = false;
	}
}

void Flame::AttackObject()
{
	//std::string unique_Flame_name = "Flame" + std::to_string(count);
	//count++;
	//GameObject* p = GameObjectManager::GetInstance().CreateObject(unique_Flame_name);
	//p->AddComponent<FlameComp>();
	//p->active_ = true;
	fl->AddComponent<FlameComp>();
	fl->active_ = true;
}

void Flame::LoadFromJson(const json&)
{
}
json Flame::SaveToJson()
{
	return json();
}
ComponentSerializer* Flame::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Flame>())
		std::cout << "Flame::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Flame>();
}
