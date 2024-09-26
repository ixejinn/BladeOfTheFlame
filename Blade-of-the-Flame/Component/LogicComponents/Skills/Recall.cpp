#include "Recall.h"

#include "../../Event/Event.h"
#include "../Monster.h"
#include "../../Utils/Utils.h"
#include <iostream>

AEVec2 Recall::pPos;

Recall::Recall(GameObject* owner) : BaseAttack(owner)
{
	owner_->AddComponent<Transform>();
	owner_->AddComponent<RigidBody>();
	owner_->AddComponent<Sprite>();
	owner->GetComponent<Sprite>()->SetTexture("Assets/glitch.png");
	mode = df;
	elapsed = 0;
	pPos = { 0, 0 };
}

Recall::~Recall()
{
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Transform>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<RigidBody>())));
	owner_->DeleteComponent(std::type_index(typeid(owner_->GetComponent<Sprite>())));
	GameObjectManager::GetInstance().RemoveObject(owner_->GetName());
}

void Recall::Update()
{
	float dt = AEFrameRateControllerGetFrameRate();
	if (mode == df)
	{
		playerlife = player_->GetComponent<Player>()->GetHp();
		playerPos = player_->GetComponent<Transform>()->GetPosition();
		for (int i = 0; i < 300; i++)
		{
			info.push_back({ playerPos, playerlife });
		}
		mode = set;
	}
	if (mode == set)
	{
		owner_->GetComponent<Transform>()->SetScale({ 0, 0 });
		check = 299;
		playerlife = player_->GetComponent<Player>()->GetHp();
		playerPos = player_->GetComponent<Transform>()->GetPosition();
		info.push_back({ playerPos, playerlife });
		if (info.size() > 300)
		{
			info.erase(info.begin());
		}
	}
	if (mode == fire)
	{
		if(check > 0 && info.size() == 300)
		{
			owner_->GetComponent<Transform>()->SetScale ({ 100, 100 });
			//ComponentManager<GraphicsComponent>::GetInstance().ToBack(static_cast<GraphicsComponent*>(owner_->GetComponent<Sprite>()));
			player_->GetComponent<Transform>()->SetPosition(info.at(check).first);
			player_->GetComponent<Player>()->SetHp(info.at(check).second);
			check--;
		}
		else
		{
			mode = set;
			player_->GetComponent<Player>()->SkillGage = 0;
		}
	}
	owner_->GetComponent<Transform>()->SetPosition(player_->GetComponent<Transform>()->GetPosition());
}

void Recall::LevelUp()
{
}

void Recall::AttackObject()
{
}

ComponentSerializer* Recall::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Recall>())
		std::cout << "Recall::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Recall>();
}

void Recall::LoadFromJson(const json&)
{
}

json Recall::SaveToJson()
{
	return json();
}
