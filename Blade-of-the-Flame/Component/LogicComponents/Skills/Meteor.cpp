#include "Meteor.h"
#include "../../AnimationComp.h"
#include "../../Manager/GameObjectManager.h"

Meteor::Meteor(GameObject* owner) : Attack(owner)
{
	int cState = ready;
	bool onoff = false;
	player_ = GameObjectManager::GetInstance().GetObjectA("player");
	owner_->active_ = false;
	owner->AddComponent<Sprite>();
	owner->AddComponent<Audio>();
	owner->AddComponent<RigidBody>();
	owner->AddComponent<Transform>();
	owner_->AddComponent<BoxCollider>();
	owner_->GetComponent<BoxCollider>()->SetType(Collider::OBB_TYPE);
}

void Meteor::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void Meteor::Update()
{
	if (onoff == true)
	{
		owner_->active_ = true;

		AEInputInit();
		s32 x, y;
		AEInputGetCursorPosition(&x, &y);
		AEVec2 mousePosF({ static_cast<float>(x), static_cast<float>(y) });
		owner_->GetComponent<Transform>()->SetScale({ 50, 50 });
		//Animation
		if (AEInputCheckCurr(AEVK_LBUTTON))
		{
			owner_->GetComponent<Transform>()->SetPosition({ mousePosF.x + 50, mousePosF.y + 700 });
			//Meteor mode : owner_->GetComponent<Sprite>()->SetTexture()
			cState = shoot;
		}
		if (cState == shoot)
		{
			AEVec2 attackDir{ x - windowWidth / 2, windowHeight / 2 - y }, unitDir;
			AEVec2Normalize(&unitDir, &attackDir);

			owner_->GetComponent<RigidBody>()->AddVelocity(unitDir / 2);
			if (owner_->GetComponent<Transform>()->GetPosition().x == mousePosF.x
				&& owner_->GetComponent<Transform>()->GetPosition().y == mousePosF.y)
			{
				//damage
				owner_->GetComponent<Sprite>()->SetColor({ 0, 0, 0 });
				owner_->GetComponent<RigidBody>()->ClearVelocity();

				onoff = false;
				cState = ready;
			}
		}
	}
}

void Meteor::LoadFromJson(const json&)
{
}

json Meteor::SaveToJson()
{
	return json();
}

ComponentSerializer* Meteor::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Meteor>())
		std::cout << "Meteor::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Meteor>();
}
