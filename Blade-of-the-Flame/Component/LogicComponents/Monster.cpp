#include "Monster.h"

#include "../../Event/Event.h"
#include "../../Manager/EventManager.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Utils/Utils.h"

Monster::Monster(GameObject* owner) : LogicComponent(owner), timeStart_()
{
	hp_ = 20;
	maxHp_ = 20;
	dmg_ = 5;
	moveSpeed_ = 10.f;
	knockback_ = 10.f;
	cooldown_ = 1.0f;
	timeStart_ = std::chrono::system_clock::now();

	/* Set Monster component */
	owner_->AddComponent<BoxCollider>();
	owner_->AddComponent<Sprite>();

	owner_->GetComponent<Transform>()->SetScale({ 30, 30 });
	//owner_->GetComponent<Sprite>()->SetColor({ 200, 100, 20 });

	BoxCollider* col = owner_->GetComponent<BoxCollider>();
	col->SetLayer(Collider::E_BODY);
	col->SetHandler(static_cast<EventEntity*>(this));
	
	/* Set pointer */
	transPlayer_ = GameObjectManager::GetInstance().GetObjectA("player")->GetComponent<Transform>();
	trans_ = owner_->GetComponent<Transform>();
	rb_ = owner_->GetComponent<RigidBody>();
}

void Monster::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void Monster::Update()
{
	AEVec2 playerPos = transPlayer_->GetPosition();
	AEVec2 pos = trans_->GetPosition();
	AEVec2 moveDir = playerPos - pos, unitMoveDir;
	f32 tmp = AEVec2SquareLength(&moveDir);

	if (hp_ <= 0 || tmp > 9 * windowHeight * windowHeight)
	{
		hp_ = maxHp_;
		owner_->SetActive(false);
	}
	else if (hp_ <= 10)
		owner_->GetComponent<Sprite>()->SetColor({ 200, 10, 10 });
	else
		owner_->GetComponent<Sprite>()->SetColor({ 200, 100, 20 });

	AEVec2 velocity = rb_->GetVelocity();
	f32 dotProduct = moveDir.x * velocity.x + moveDir.y * velocity.y;
	if (dotProduct < 0)
		rb_->ClearVelocity();

	AEVec2Normalize(&unitMoveDir, &moveDir);
	rb_->AddVelocity(unitMoveDir * moveSpeed_);
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

}

void Monster::OnCollision(CollisionEvent* event)
{
	Player* player = event->from_->GetComponent<Player>();
	if (player)
	{
		std::chrono::duration<double> dt = std::chrono::system_clock::now() - timeStart_;
		if (dt.count() >= cooldown_)
		{
			timeStart_ = std::chrono::system_clock::now();

			player->AddHp(-dmg_);
		}
		return;
	}

	MeleeAttack* melee = event->from_->GetComponent<MeleeAttack>();
	if (melee)
	{
		hp_ -= melee->GetDmg();

		RigidBody* rb = owner_->GetComponent<RigidBody>();
		AEVec2 velocity = rb->GetVelocity();
		rb->ClearVelocity();
		rb->AddVelocity(velocity * -knockback_);

		return;
	}
}

ComponentSerializer* Monster::CreateComponent(GameObject* owner)
{
	return nullptr;
}
