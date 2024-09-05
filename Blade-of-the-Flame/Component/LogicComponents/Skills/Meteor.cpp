#include "Meteor.h"
#include "../../Event/Event.h"
#include "../../Manager/EventManager.h"
#include "../../AnimationComp.h"
#include "../../Manager/SkillManager.h" 
#include <iostream>
#include "AEUtil.h"

Meteor::Meteor(GameObject* owner) : BaseAttack(owner)
{
	owner->active_ = false;
	dmg_ = 20;
	range_ = 700.f;
	cooldown_ = 0;
	dmgGrowthRate_ = 10.f;
	cState = df;
	temp = dmg_;
	owner->AddComponent<Transform>();
	owner->AddComponent<RigidBody>();
	owner->AddComponent<Sprite>();
	owner->AddComponent<AnimationComp>();
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/MeteorAnime/Meteor1.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/MeteorAnime/Meteor2.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/MeteorAnime/Meteor3.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/MeteorAnime/Meteor4.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/MeteorAnime/Meteor5.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/MeteorAnime/Meteor6.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/MeteorAnime/Meteor7.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/MeteorAnime/Meteor8.png", "Attack");
	owner->GetComponent<AnimationComp>()->AddDetail("Assets/MeteorAnime/MagicCircle.png", "Idle");
	owner->GetComponent<AnimationComp>()->SetTerm(200.0f);
	owner->GetComponent<RigidBody>()->ClearVelocity();
	owner_->GetComponent<Transform>()->SetScale({ range_, range_ });
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

void Meteor::Update()
{
	if (!AEInputCheckCurr(AEVK_LBUTTON) && cState == df)
		cState = ready;
	if (cState == ready)
	{
		dmg_ = 0;
		AEInputInit();
		s32 x, y;
		AEInputGetCursorPosition(&x, &y);
		AEVec2 mousePosF({ static_cast<float>(x), static_cast<float>(y) });
		owner_->GetComponent<Transform>()->SetScale({ 300, 300 });
		owner_->GetComponent<Transform>()->SetPosition(convert(mousePosF));
		convertPos = convert(mousePosF);
		//MagicCircle mode
		owner_->GetComponent<AnimationComp>()->ChangeAnimation("Idle");
		if (AEInputCheckCurr(AEVK_LBUTTON))
		{
			owner_->GetComponent<Transform>()->SetPosition(convertPos.x + startingOffset.x, convertPos.y + startingOffset.y);
			//Meteor mode
			owner_->GetComponent<AnimationComp>()->ChangeAnimation("Attack");
			cState = shoot;
			meteorLifetime = 11000;
		}
	}
	else if (cState == shoot)
	{
		AEVec2 attackDir{ convertPos -  owner_->GetComponent<Transform>()->GetPosition()}, unitDir;
		AEVec2Normalize(&unitDir, &attackDir);
	
		owner_->GetComponent<RigidBody>()->AddVelocity(unitDir * 200);

		meteorLifetime -= AEFrameRateControllerGetFrameRate();
		std::cout << meteorLifetime <<std::endl;
		if (meteorLifetime <= 0)
		{
			AttackObject();
			owner_->GetComponent<RigidBody>()->ClearVelocity();
			cState = df;
			SkillManager::GetInstance().CooldownCountMeteor = 0;
			SkillManager::GetInstance().resetKeys();
			player_->GetComponent<Player>()->curAttack_ = nullptr;
			owner_->active_ = false;
		}
	}
}

void Meteor::LevelUp()
{
	temp += int(temp * dmgGrowthRate_ / 100);
}

void Meteor::AttackObject()
{
	dmg_ = temp;
}

void Meteor::LoadFromJson(const json&)
{
}

json Meteor::SaveToJson()
{
	return json();
}

ComponentSerializer* Meteor::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Meteor>())
		std::cout << "Meteor::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Meteor>();
}
