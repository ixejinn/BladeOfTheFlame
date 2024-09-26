#include "BaseMonster.h"

#include "AEVec2.h"
#include "../../../Manager/ComponentManager.h"
#include "../../../Manager/GameObjectManager.h"
#include "../../../Event/Event.h"
#include "../Skills/shield.h"

namespace Manager
{
	extern GameObjectManager& objMgr;
}

BaseMonster::BaseMonster(GameObject* owner) : LogicComponent(owner)
{
	knockback_ = 10.f;
	cooldown_ = 1.0;
	timeStart_ = std::chrono::system_clock::now();

	/* Set components */
	owner_->AddComponent<BoxCollider>();

	BoxCollider* col = owner_->GetComponent<BoxCollider>();
	col->SetLayer(Collider::E_BODY);
	col->SetHandler(static_cast<EventEntity*>(this));

	/* Set pointers */
	playerTrans_ = Manager::objMgr.GetObjectA("player")->GetComponent<Transform>();
	trans_ = owner_->GetComponent<Transform>();
	rb_ = owner_->GetComponent<RigidBody>();
}

void BaseMonster::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void BaseMonster::LoadFromJson(const json&)
{
}

json BaseMonster::SaveToJson()
{
	return json();
}

void BaseMonster::OnEvent(BaseEvent* event)
{
}

void BaseMonster::OnCollision(CollisionEvent* event)
{
	Player* player = event->from_->GetComponent<Player>();
	if (player)
	{
		std::chrono::duration<double> dt = std::chrono::system_clock::now() - timeStart_;
		if (dt.count() >= cooldown_)
		{
			timeStart_ = std::chrono::system_clock::now();

			if (player->shield_Attack->GetComponent<Shield>()->ac == true)
				player->AddHp(-dmg_ / 7);
			else
				player->AddHp(-dmg_);
		}

		return;
	}

	MeleeAttack* melee = event->from_->GetComponent<MeleeAttack>();
	if (melee != nullptr && melee->mode == MeleeAttack::fire)
	{
		hp_ -= melee->GetDmg();
		Manager::objMgr.GetObjectA("player")->GetComponent<Player>()->SkillGage += 1;

		AEVec2 velocity = rb_->GetVelocity();
		rb_->ClearVelocity();
		rb_->AddVelocity(velocity * -knockback_);

		state_ = HURT;

		return;
	}

	Monster* other = event->from_->GetComponent<Monster>();
	if (other)
	{
		AEVec2 otherVelocity = event->from_->GetComponent<RigidBody>()->GetVelocity();
		rb_->ClearVelocity();
		rb_->AddVelocity(otherVelocity);

		return;
	}
}
