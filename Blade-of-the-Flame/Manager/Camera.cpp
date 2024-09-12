#include "Camera.h"

#include "GameObjectManager.h"

Camera::Camera() : world_to_ndc_xform()
{
}

Camera::~Camera()
{

}

void Camera::Update()
{
	GameObject* player = GameObjectManager::GetInstance().GetObjectA("player");
	if (player)
	{
		AEVec2 playerPos = player->GetComponent<Transform>()->GetPosition();
		SetPos(playerPos.x, playerPos.y);
	}
	
	AEMtx33Identity(&world_to_ndc_xform);

	AEMtx33TransApply(&world_to_ndc_xform, &world_to_ndc_xform, -srcX, -srcY);

	AEMtx33ScaleApply(&world_to_ndc_xform, &world_to_ndc_xform, height, height);
}

void Camera::AddHeight(float value)
{

}

void Camera::SetHeight(float value)
{
	height = AEClamp(value, 0.5, 10);
}

void Camera::SetPos(float _x, float _y)
{
	srcX = _x;
	srcY = _y;
}

