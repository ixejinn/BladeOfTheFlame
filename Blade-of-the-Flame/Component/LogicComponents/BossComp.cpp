//#include "BossComp.h"
//#include "../../Manager/GameObjectManager.h"
//
//BossComp::BossComp(GameObject* owner) : LogicComponent(owner)
//{
//	player = GameObjectManager::GetInstance().GetObjectA("player");
//
//	owner_->AddComponent<BoxCollider>();
//	owner_->AddComponent<Sprite>();
//
//	Transform* trans_ = owner_->GetComponent<Transform>();
//	trans_->SetScale({ 200, 200 });
//	trans_->SetPosition({ 400,400 });
//
//	BoxCollider* col = owner_->GetComponent<BoxCollider>();
//	col->SetLayer(Collider::E_BODY);
//	col->SetHandler(static_cast<EventEntity*>(this));
//
//	owner_->GetComponent<Sprite>()->SetTexture("Assets/yee.png");
//
//	timeStart_ = std::chrono::system_clock::now();
//}
//
//GameObject* BossComp::CreateBulletObj()
//{
//	std::string unique_bullet_name = "bullet" + std::to_string(bullet.size());
//	GameObject* addBullet = GameObjectManager::GetInstance().CreateObject(unique_bullet_name);
//	bullet.push_back(addBullet);
//	addBullet->AddComponent<BulletComp>();
//
//	return addBullet;
//}
//
//void BossComp::RemoveFromManager()
//{
//	//TODO::
//}
//
//ComponentSerializer* BossComp::CreateComponent(GameObject* owner)
//{
//	return nullptr;
//}