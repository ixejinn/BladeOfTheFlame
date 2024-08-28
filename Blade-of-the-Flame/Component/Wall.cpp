#include "Wall.h"

#include "../GameObject/GameObject.h"

Wall::Wall(GameObject* owner) : LogicComponent(owner) {}

void Wall::Update()
{
}

void Wall::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");
	if (compData != data.end()) {}
}

json Wall::SaveToJson()
{
	json data, compData;
	data["type"] = typeName;

	data["compData"] = compData;
	return data;
}

ComponentSerializer* Wall::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Wall>())
		std::cout << "Wall::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Wall>();
}
