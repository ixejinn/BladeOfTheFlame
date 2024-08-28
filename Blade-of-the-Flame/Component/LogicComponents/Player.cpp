#include "Player.h"

#include <typeindex>
#include "../../GameObject/GameObject.h"
#include "../../Event/Event.h"
#include "../../Manager/EventManager.h"

Player::Player(GameObject* owner) : LogicComponent(owner)
{
	//// TODO: GameObject에 Component 담는 순서 주의, Serializer 부분 수정 필요
	PlayerController* pc = owner_->GetComponent<PlayerController>();
	if (!pc)
		std::cerr << "Player::Player() PlayerController not found" << std::endl;

	pc->MultiplyMoveSpeed(moveSpeed_);
}

void Player::Update()
{
	if (exp_ >= maxExp_)
		LevelUp();

	if (hp_ <= 0)
	{
		GameOverEvent* event{ new GameOverEvent() };
		event->from_ = owner_;
		EventManager::GetInstance().AddEvent(event);
	}
}

void Player::LoadFromJson(const json& data)
{
}

json Player::SaveToJson()
{
	return json();
}

void Player::OnEvent(BaseEvent* event)
{
	std::type_index eventType = std::type_index(typeid(*event));

	// Collision event
	if (eventType == std::type_index(typeid(CollisionEvent)))
	{
		//// TODO: 해당 부분 Collision system 수정 필요
		if (dynamic_cast<CollisionEvent*>(event)->to_ != owner_)
			return;


	}
}

void Player::LevelUp()
{
	if (level_ >= maxLevel_)
		return;

	level_++;
	exp_ = 0;

	maxHp_ += maxHp_ * hpGrowthRate_ / 100;
	hp_ = maxHp_;

	baseDmg_ += baseDmg_ * baseDmgGrowthRate_ / 100;
	
	if (level_ == 3)
		attackRange_ = 7;
}

ComponentSerializer* Player::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Player>())
		std::cout << "Transform::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Player>();
}
