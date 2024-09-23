#include "Utils.h"
#include "../Manager/GameObjectManager.h"

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