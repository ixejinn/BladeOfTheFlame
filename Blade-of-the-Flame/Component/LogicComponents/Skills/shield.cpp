#include "shield.h"

Shield::Shield(GameObject* owner) : BaseAttack(owner)
{
	ac = false;
	dmg_ = 0;
	dmgGrowthRate_ = 0;
	owner->AddComponent<Transform>();
	owner->AddComponent<RigidBody>();
	owner->AddComponent<Sprite>();
	owner->AddComponent<AnimationComp>();
	for (int i = 1; i < 21; i++)
	{
		owner->GetComponent<AnimationComp>()->AddDetail("Assets/shieldAnime/" + std::to_string(i) + ".png", "Attack");
	}
	owner->GetComponent<AnimationComp>()->ChangeAnimation("Attack");
	owner->GetComponent<AnimationComp>()->SetTerm(100);
	owner->GetComponent<Transform>()->SetScale({ 100, 100 });
}

Shield::~Shield()
{
}

void Shield::Update()
{
	if (mode == set)
	{
		ac = true;
		lifetime = 30000;
		mode = fire;
	}
	else if (mode == fire)
	{
		owner_->GetComponent<Transform>()->SetPosition(player_->GetComponent<Transform>()->GetPosition());
		float dt = AEFrameRateControllerGetFrameRate();
		lifetime -= dt;

		if (lifetime <= 0)
		{
			ac = false;
			mode = set;
			owner_->active_ = false;
		}
	}
}

void Shield::LevelUp()
{
}

void Shield::AttackObject()
{
}

void Shield::LoadFromJson(const json&)
{
}

json Shield::SaveToJson()
{
	return json();
}

ComponentSerializer* Shield::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Shield>())
		std::cout << "Shield::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Shield>();
}

void Shield::OnEvent(BaseEvent*)
{
}

void Shield::OnCollision(CollisionEvent*)
{
}
