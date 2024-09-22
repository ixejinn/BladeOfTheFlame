#include "Camera.h"

#include "GameObjectManager.h"

namespace Manager
{
	extern GameObjectManager& objMgr;
}

Camera::Camera() : world_to_ndc_xform()
{
}

Camera::~Camera()
{

}

void Camera::UpdatePositionBasedOnPlayer()
{
	GameObject* obj = Manager::objMgr.GetObjectA("player");
	if (obj)
	{
		AEVec2 playerPos = obj->GetComponent<Transform>()->GetPosition();
		SetPos(playerPos.x, playerPos.y);
	}

	obj = Manager::objMgr.GetObjectA("ScreenEffect");
	if (obj)
		obj->GetComponent<ScreenOverlay>()->Update();

	obj = Manager::objMgr.GetObjectA("bossBar");
	if (obj)
		obj->GetComponent<FillBar>()->UpdatePositionBasedOnPlayer();

	obj = Manager::objMgr.GetObjectA("monsterBar");
	if (obj)
		obj->GetComponent<FillBar>()->UpdatePositionBasedOnPlayer();

	obj = Manager::objMgr.GetObjectA("expBar");
	if (obj)
		obj->GetComponent<FillBar>()->UpdatePositionBasedOnPlayer();

	obj = Manager::objMgr.GetObjectA("healthBar");
	if (obj)
		obj->GetComponent<FillBar>()->UpdatePositionBasedOnPlayer();
}

void Camera::Update()
{
	UpdatePositionBasedOnPlayer();
	
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

