#include "UiComp.h"
#include "../../Component/Sprite.h"

UiComp::UiComp(GameObject* owner) : LogicComponent(owner)
{
	owner_->AddComponent<Sprite>();
	UItrans_ = owner_->GetComponent<Transform>();
}

void UiComp::Update()
{

}

void UiComp::RemoveFromManager()
{

}

ComponentSerializer* UiComp::CreateComponent(GameObject* owner)
{
	return nullptr;
}
