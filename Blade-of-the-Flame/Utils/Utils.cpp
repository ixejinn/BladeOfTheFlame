#include "Utils.h"
#include "../Manager/GameStateManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/ComponentManager.h"
#include "../Manager/EventManager.h"
#include "../Manager/GameObjectManager.h"
#include "../Manager/ExpItemManager.h"
#include "../Manager/MonsterManager.h"

namespace Manager
{
	ResourceManager& rscMgr = ResourceManager::GetInstance();

	ComponentManager<EngineComponent>& compEngMgr = ComponentManager<EngineComponent>::GetInstance();
	ComponentManager<AudioComponent>& compAudMgr = ComponentManager<AudioComponent>::GetInstance();
	ComponentManager<GraphicsComponent>& compGfxMgr = ComponentManager<GraphicsComponent>::GetInstance();
	ComponentManager<LogicComponent>& compLgcMgr = ComponentManager<LogicComponent>::GetInstance();

	GameObjectManager& objMgr = GameObjectManager::GetInstance();
	GameStateManager& gsMgr = GameStateManager::GetInstance();

	EventManager& evntMgr = EventManager::GetInstance();

	ExpItemManager& expMgr = ExpItemManager::GetInstance();
	MonsterManager& monMgr = MonsterManager::GetInstance();
}

AEVec2 convert(AEVec2 a)
{
	AEVec2 worldPos;
	worldPos.x = a.x - windowWidth / 2;
	worldPos.y = -a.y + windowHeight / 2;
	AEVec2 pos = GameObjectManager::GetInstance().GetObjectA("player")->GetComponent<Transform>()->GetPosition();
	AEVec2 result;
	result.x = worldPos.x + pos.x;
	result.y = worldPos.y + pos.y;
	return result;
}