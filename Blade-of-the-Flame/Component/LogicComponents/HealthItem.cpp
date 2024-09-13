#include "HealthItem.h"

#include "../../Event/Event.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Manager/ItemManager.h"

HealthItem::HealthItem(GameObject* owner) : BaseItem(owner)
{
	owner_->GetComponent<Transform>()->SetScale({ 50, 50 });
	owner_->GetComponent<BoxCollider>()->SetLayer(Collider::ITEM);
	//owner_->GetComponent<Sprite>()->SetColor({ 255, 0, 0 });
	owner_->GetComponent<Sprite>()->SetTexture("Assets/cookie.png");

	trans_ = owner_->GetComponent<Transform>();

	GameObject* player = GameObjectManager::GetInstance().GetObjectA("player");
	playerTrans_ = player->GetComponent<Transform>();
	player_ = player->GetComponent<Player>();
}

void HealthItem::Update()
{
	if (use_)
	{
		player_->AddHp(hp_);

		use_ = false;
		owner_->active_ = false;
		ItemManager::GetInstance().Release(owner_);
	}
	else
	{
		AEVec2 playerPos = playerTrans_->GetPosition();
		AEVec2 pos = trans_->GetPosition();
		AEVec2 dir = playerPos - pos;
		f32 squareDist = AEVec2SquareLength(&dir);

		if (squareDist > 9 * windowHeight * windowHeight)
			ItemManager::GetInstance().Release(owner_);
	}
}

void HealthItem::LoadFromJson(const json&)
{
}

json HealthItem::SaveToJson()
{
	return json();
}

void HealthItem::OnEvent(BaseEvent* event)
{
}

void HealthItem::OnCollision(CollisionEvent* event)
{
	Player* player = event->from_->GetComponent<Player>();
	if (player)
		use_ = true;
}

ComponentSerializer* HealthItem::CreateComponent(GameObject* owner)
{
	return nullptr;
}
