#pragma once
#include <string>
#include <map>

class ComponentSerializer;
class GameObject;

class Registry
{
private:
	std::map<std::string, ComponentSerializer* (*)(GameObject* owner)> componentMap;

	Registry();
	~Registry() = default;

	Registry(const Registry&) = delete;
	Registry& operator =(const Registry&) = delete;
	Registry(Registry&&) = delete;
	Registry& operator =(Registry&&) = delete;

	// StateSerializer에서만 사용
	ComponentSerializer* CreateComponent(const std::string& typeName, GameObject* owner);

public:
	static Registry& GetInstance()
	{
		static Registry instance;
		return instance;
	}

	friend class StateSerializer;
};