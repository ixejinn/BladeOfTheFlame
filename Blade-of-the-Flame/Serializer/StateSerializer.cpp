#include "StateSerializer.h"

#include <fstream>
#include <iostream>
#include "ComponentSerializer.h"
#include "Registry.h"
#include "../Manager/GameObjectManager.h"
#include "json.hpp"

void StateSerializer::LoadState(const std::string& filename)
{
	std::fstream file;
	file.open(filename, std::fstream::in);

	if (!file.is_open())
	{
		std::cerr << "[ERROR] StateSerializer::LoadState Unable to open the file " << filename << std::endl;
		return;
	}

	json allData;
	file >> allData;

	for (auto& objData : allData)
	{
		GameObject* obj = GameObjectManager::GetInstance().CreateObject();
		
		auto objIt = objData.find("object");
		if (objIt != objData.end())
		{
			// transform components
			auto compIt = objData.find("transform");
			if (compIt == objData.end())
				continue;
			
			for (auto& comp : *compIt)
			{
				auto compDataIt = comp.find("type");
				if (compDataIt == comp.end())
					continue;

				ComponentSerializer* ptr = Registry::GetInstance().CreateComponent(Transform::TypeName, obj);
				if (ptr != nullptr)
					ptr->LoadFromJson(comp);
			}

			// other components
			compIt = objData.find("components");
			if (compIt == objData.end())
				continue;

			for (auto& comp : *compIt)
			{
				auto compDataIt = comp.find("type");
				if (compDataIt == comp.end())
					continue;

				std::string typeName = compDataIt.value().dump();
				typeName = typeName.substr(1, typeName.size() - 2);

				ComponentSerializer* ptr = Registry::GetInstance().CreateComponent(typeName, obj);
				if (ptr != nullptr)
					ptr->LoadFromJson(comp);
			}
		}
	}
}

void StateSerializer::SaveState(const std::string& filename)
{
	json allData;

	for (const auto& objIt : GameObjectManager::GetInstance().GetAllObjects())
	{
		json objData, transform, compData;
		GameObject* obj = objIt.second.get();

		objData["object"] = obj->GetName();

		for (const auto& compIt : obj->GetAllComponents())
		{
			Component* comp = compIt.second;

			if (dynamic_cast<Transform*>(comp) != nullptr)
				transform.push_back(comp->SaveToJson());
			else
				compData.push_back(comp->SaveToJson());
		}
		objData["transform"] = transform;
		objData["components"] = compData;
		allData.push_back(objData);
	}

	std::fstream file;
	file.open(filename, std::fstream::out);

	if (!file.is_open())
	{
		std::cerr << "[ERROR] StateSerializer::SaveState Unable to open the file " << filename << std::endl;
		return;
	}

	file << std::setw(2) << allData;
	file.close();
}
