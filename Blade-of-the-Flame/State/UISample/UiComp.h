#pragma once
#include "AEEngine.h"
#include "../../Component/LogicComponent.h"
#include "../../Manager/ComponentManager.h"
class Sprite;

class UiComp : public LogicComponent
{
protected:

	GameObject* UI_;
	Text* UItext_;
	Transform* UItrans_;
	Sprite* UIDraw_;

	UiComp(GameObject* owner);

public:
	void Update() override;

	void RemoveFromManager() override;

	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<LogicComponent>;
};
