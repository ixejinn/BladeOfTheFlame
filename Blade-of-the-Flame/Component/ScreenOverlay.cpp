#include "ScreenOverlay.h"

#include <typeindex>
#include "../Event/Event.h"
#include "../Manager/EventManager.h"
#include "../Manager/GameObjectManager.h"
#include "../Utils/Utils.h"

namespace Manager
{
	extern GameObjectManager& objMgr;
	extern EventManager& evntMgr;
}

ScreenOverlay::ScreenOverlay(GameObject* owner) : LogicComponent(owner), textureName()
{
	textureName[0] = "Assets/dark50.png";
	textureName[1] = "Assets/dark75.png";
	textureName[2] = "Assets/dark100.png";
	textureName[3] = "Assets/darkFinal.png";

	owner_->AddComponent<Transform>();
	owner_->AddComponent<Sprite>();

	trans_ = owner_->GetComponent<Transform>();
	trans_->SetScale({ windowWidth, windowHeight });

	sp_ = owner_->GetComponent<Sprite>();
	sp_->SetTexture(textureName[0]);

	playerTrans_ = Manager::objMgr.GetObjectA("player")->GetComponent<Transform>();

	Manager::evntMgr.RegisterEntity(std::type_index(typeid(IncreaseBrightness)), static_cast<EventEntity*>(this));
}

void ScreenOverlay::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void ScreenOverlay::Update()
{
	trans_->SetPosition(playerTrans_->GetPosition());
}

void ScreenOverlay::LoadFromJson(const json&)
{
}

json ScreenOverlay::SaveToJson()
{
	return json();
}

void ScreenOverlay::OnEvent(BaseEvent* event)
{
	IncreaseBrightness* e = static_cast<IncreaseBrightness*>(event);
	int idx = e->level;
	if (idx < 4)
		sp_->SetTexture(textureName[e->level]);
}

void ScreenOverlay::OnCollision(CollisionEvent* event)
{
}

ComponentSerializer* ScreenOverlay::CreateComponent(GameObject* owner)
{
	return nullptr;
}
