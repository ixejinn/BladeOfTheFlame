#include "MagnetItem.h"

#include "../../../Event/Event.h"
#include "../../../Manager/GameObjectManager.h"
#include "../../../Manager/ItemManager.h"

MagnetItem::MagnetItem(GameObject* owner) : BaseItem(owner)
{
	activeTime = 5.0;

	owner_->GetComponent<Transform>()->SetScale({ 50, 50 });
	owner_->GetComponent<BoxCollider>()->SetLayer(Collider::ITEM);
	//owner_->GetComponent<Sprite>()->SetColor({ 255, 0, 255 });
	owner_->GetComponent<Sprite>()->SetTexture("Assets/magnet.png");

	trans_ = owner_->GetComponent<Transform>();

	GameObject* player = GameObjectManager::GetInstance().GetObjectA("player");
	playerCircle_ = player->GetComponent<CircleCollider>();
	playerTrans_ = player->GetComponent<Transform>();
}

void MagnetItem::Update()
{
	if (use_)
	{
		if (firstUse_)
		{
			timeStart_ = std::chrono::system_clock::now();
			preRadius_ = playerCircle_->GetRadius();
			playerCircle_->MultiplyRadius(radiusMultiple_);
			firstUse_ = false;
			return;
		}
		else
		{
			AEVec2 pos = playerTrans_->GetPosition();
			pos.y -= windowHeight / 2;
			pos.y += 50;
			trans_->SetPosition(pos);
		}

		std::chrono::duration<double> dt = std::chrono::system_clock::now() - timeStart_;
		if (dt.count() >= activeTime)
		{
			//playerCircle_->SetRadius(preRadius_);
			playerCircle_->MultiplyRadius(1 / radiusMultiple_);

			firstUse_ = true;
			use_ = false;
			owner_->active_ = false;
			ItemManager::GetInstance().Release(ItemManager::MAGNET, owner_);
		}
	}
	else if (DeactiveIfFar())
		ItemManager::GetInstance().Release(ItemManager::MAGNET, owner_);
}

void MagnetItem::LoadFromJson(const json&)
{
}

json MagnetItem::SaveToJson()
{
	return json();
}

void MagnetItem::OnEvent(BaseEvent* event)
{
}

//void MagnetItem::OnCollision(CollisionEvent* event)
//{
//	Player* player = event->from_->GetComponent<Player>();
//	if (player)
//		use_ = true;
//}

ComponentSerializer* MagnetItem::CreateComponent(GameObject* owner)
{
	return nullptr;
}
