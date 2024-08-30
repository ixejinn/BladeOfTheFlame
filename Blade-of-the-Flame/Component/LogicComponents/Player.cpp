#include "Player.h"

#include <typeindex>
#include "AEGraphics.h"
#include "../../Event/Event.h"
#include "../../Manager/EventManager.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Utils/Utils.h"

Player::Player(GameObject* owner) : LogicComponent(owner)
{
	timeStart_ = std::chrono::system_clock::now();

	/* Set Player component */
	owner_->AddComponent<BoxCollider>();
	owner_->AddComponent<Sprite>();
	owner_->AddComponent<PlayerController>();

	/* BASIC ATTACK GameObject */
	meleeAttack_ = GameObjectManager::GetInstance().CreateObject("playerMeleeAttack");
	meleeAttack_->AddComponent<MeleeAttack>();
	meleeAttack_->GetComponent<MeleeAttack>()->SetPlayer(owner_);
	//rangedAttack_ = GameObjectManager::GetInstance().CreateObject("playerRangedAttack");

	curAttack_ = meleeAttack_->GetComponent<MeleeAttack>();

	owner_->GetComponent<PlayerController>()->MultiplyMoveSpeed(moveSpeed_);

	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(CollisionEvent)), static_cast<EventEntity*>(this));
}

void Player::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void Player::Update()
{
	/* CHECK */
	// Level up
	if (exp_ >= maxExp_)
		LevelUp();

	// Death
	if (hp_ <= 0)
	{
		GameOverEvent* event{ new GameOverEvent() };
		event->from_ = owner_;
		EventManager::GetInstance().AddEvent(event);
	}

	/* SET CAMERA */
	Transform* trans = owner_->GetComponent<Transform>();
	AEVec2 pos = trans->GetPosition();
	AEGfxSetCamPosition(pos.x, pos.y);

	/* ATTACK */
	std::chrono::duration<double> dt = std::chrono::system_clock::now() - timeStart_;
	if (dt.count() >= curAttack_->GetCooldown() && AEInputCheckCurr(AEVK_LBUTTON))
	{
		timeStart_ = std::chrono::system_clock::now();

		//std::cout << x << ", " << y << std::endl;
		curAttack_->AttackObject();
	}
	//else
		//GameObjectManager::GetInstance().GetObjectA("playerMeleeAttack")->active_ = false;
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
		CollisionEvent* colEvent = static_cast<CollisionEvent*>(event);

		//// TODO: 해당 부분 Collision system 수정 필요
		if (colEvent->to_ != owner_ ||
			colEvent->attackMonster)
			return;


	}
}

void Player::LevelUp()
{
	if (level_ >= maxLevel_)
		return;

	level_++;
	exp_ = 0;

	maxHp_ += int(maxHp_ * hpGrowthRate_ / 100);
	hp_ = maxHp_;
	
	//if (level_ == 3)
	//	curAttack_ = rangedAttack_;
}

ComponentSerializer* Player::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Player>())
		std::cout << "Transform::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Player>();
}
