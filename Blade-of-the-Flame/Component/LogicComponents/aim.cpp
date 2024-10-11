#include "aim.h"

aim::aim(GameObject* owner) : LogicComponent(owner)
{
	owner->AddComponent<Transform>();
	owner->AddComponent<Sprite>();
	owner->AddComponent<AnimationComp>();

	owner->GetComponent<AnimationComp>()->AddDetail("Assets/aim.png", "Idle");
	owner->GetComponent<AnimationComp>()->ChangeAnimation("Idle");
	owner->GetComponent<Transform>()->SetScale({ 50, 50 });
	spin = 0;
}

aim::~aim()
{
}

void aim::Update()
{
	AEInputInit();
	s32 x, y;
	AEInputGetCursorPosition(&x, &y);
	AEVec2 mousePosF({ static_cast<float>(x), static_cast<float>(y) });
	owner_->GetComponent<Transform>()->SetRotation(spin);
	spin += AEFrameRateControllerGetFrameRate()/1000;
	owner_->GetComponent<Transform>()->SetPosition(convert(mousePosF));
}

void aim::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

ComponentSerializer* aim::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<aim>())
		std::cout << "aim::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<aim>();
}
