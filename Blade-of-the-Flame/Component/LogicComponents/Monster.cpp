#include "Monster.h"

#include "../../Event/Event.h"
#include "../../Manager/EventManager.h"
#include "../../Manager/GameObjectManager.h"

Monster::Monster(GameObject* owner) : LogicComponent(owner)
{
	timeStart_ = std::chrono::system_clock::now();

	/* Set Monster component */
	owner_->AddComponent<BoxCollider>();
	owner_->AddComponent<Sprite>();

	owner_->GetComponent<Transform>()->SetScale({ 30, 30 });
	
	EventManager::GetInstance().RegisterEntity(std::type_index(typeid(CollisionEvent)), static_cast<EventEntity*>(this));

	transPlayer = GameObjectManager::GetInstance().GetObjectA("player")->GetComponent<Transform>();
	trans = owner_->GetComponent<Transform>();
	rb = owner_->GetComponent<RigidBody>();
}

void Monster::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void Monster::Update()
{
	if (hp_ <= 0)
		owner_->active_ = false;
	else if (hp_ <= 10)
		owner_->GetComponent<Sprite>()->SetColor({ 200, 10, 10 });
	else
		owner_->GetComponent<Sprite>()->SetColor({ 200, 100, 20 });

	AEVec2 playerPos = transPlayer->GetPosition();
	AEVec2 pos = trans->GetPosition();
	AEVec2 moveDir = playerPos - pos, unitMoveDir;
	AEVec2Normalize(&unitMoveDir, &moveDir);

	rb->AddVelocity(unitMoveDir * moveSpeed_);
}

void Monster::LoadFromJson(const json&)
{
}

json Monster::SaveToJson()
{
	return json();
}

void Monster::OnEvent(BaseEvent* event)
{
	std::type_index eventType = std::type_index(typeid(*event));

	// Collision event
	if (eventType == std::type_index(typeid(CollisionEvent)))
	{
		CollisionEvent* colEvent = static_cast<CollisionEvent*>(event);

		if (colEvent->from_ == owner_ && colEvent->to_->GetComponent<Player>())
		{
			std::chrono::duration<double> dt = std::chrono::system_clock::now() - timeStart_;
			if (dt.count() >= cooldown_)
			{
				timeStart_ = std::chrono::system_clock::now();

				MonsterAttackPlayer* event{ new MonsterAttackPlayer() };
				event->from_ = owner_;
				event->dmg = dmg_;
				EventManager::GetInstance().AddEvent(static_cast<BaseEvent*>(event));
			}
		}


		if (colEvent->to_ != owner_)
			return;

		if (colEvent->attackMonster)
		{
			if (colEvent->from_->GetComponent<MeleeAttack>())
				hp_ -= colEvent->from_->GetComponent<MeleeAttack>()->GetDmg();
		}
	}
}

ComponentSerializer* Monster::CreateComponent(GameObject* owner)
{
	return nullptr;
}
