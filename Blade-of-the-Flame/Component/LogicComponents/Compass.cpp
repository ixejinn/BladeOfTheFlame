#include "Compass.h"

#include <typeindex>
#include "../../Manager/GameObjectManager.h"
#include "../../Manager/EventManager.h"
#include "../../Event/Event.h"

const float pi = float(std::atan(1)) * 4.f;

Compass::Compass(GameObject* owner) : LogicComponent(owner)
{
	owner_->AddComponent<Transform>();
	owner_->AddComponent<Sprite>();

	trans_ = owner_->GetComponent<Transform>();
	Sprite* sp = owner_->GetComponent<Sprite>();
	sp->SetAnchor(Sprite::LEFT_CENTER);
	sp->SetColor({ 255, 255, 255 });
	sp->SetTexture("Assets/lightline.png");

	playerTrans_ = GameObjectManager::GetInstance().GetObjectA("player")->GetComponent<Transform>();
	owner_->active_ = false;

	EventManager& eventMgr = EventManager::GetInstance();
	eventMgr.RegisterEntity(std::type_index(typeid(SpawnBossEvent)), static_cast<EventEntity*>(this));
	eventMgr.RegisterEntity(std::type_index(typeid(CompassActiveEvent)), static_cast<EventEntity*>(this));
}

void Compass::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void Compass::Update()
{
	AEVec2 dir = destTrans_->GetPosition() - playerTrans_->GetPosition();
	f32 dist = AEVec2Length(&dir);

	trans_->SetScale({ dist, 2.f });
	trans_->SetRotation(dir);
	trans_->SetPosition(playerTrans_->GetPosition());
}

void Compass::LoadFromJson(const json&)
{
}

json Compass::SaveToJson()
{
	return json();
}

void Compass::OnEvent(BaseEvent* event)
{
	if (event->from_->GetComponent<FillBar>())
	{
		GameObjectManager::GetInstance().GetObjectA("player")->GetComponent<Player>()->getCompass_ = true;
		owner_->active_ = true;
	}
	else if (event->from_->GetComponent<FlameAltar>())
		owner_->active_ = false;
}

void Compass::OnCollision(CollisionEvent* event)
{
}

void Compass::SetDestination(GameObject* obj)
{
	destination_ = obj->GetComponent<FlameAltar>();
	destTrans_ = obj->GetComponent<Transform>();
}

ComponentSerializer* Compass::CreateComponent(GameObject* owner)
{
	return nullptr;
}
