#include "GameObject.h"

#include <iostream>
#include <type_traits>	// std::is_base_of<Base, Derived>
#include "../Manager/ComponentManager.h"
#include "../Components.h"

template<typename T>
inline bool GameObject::AddComponent()
{
	auto type = std::type_index(typeid(T));

	if (components_.find(type) != components_.end())
	{
		std::cout << "GameObject<" << typeid(T).name() << ">::AddComponent() Already exist" << std::endl;
		return false;
	}

	T* comp = nullptr;
	if constexpr (std::is_base_of<EngineComponent, T>::value)
		comp = ComponentManager<EngineComponent>::GetInstance().CreateComponent<T>(this);
	else if constexpr (std::is_base_of<GraphicsComponent, T>::value)
		comp = ComponentManager<GraphicsComponent>::GetInstance().CreateComponent<T>(this);
	else if constexpr (std::is_base_of<LogicComponent, T>::value)
		comp = ComponentManager<LogicComponent>::GetInstance().CreateComponent<T>(this);
	else if constexpr (std::is_base_of<AudioComponent, T>::value)
		comp = ComponentManager<AudioComponent>::GetInstance().CreateComponent<T>(this);
	else
	{
		std::cerr << "[ERROR] GameObject::AddComponent() Invalid component type " << typeid(T).name() << std::endl;
		return false;
	}

	components_[type] = static_cast<Component*>(comp);
	return true;
}

template<typename T>
inline T* GameObject::GetComponent()
{
	auto type = std::type_index(typeid(T));
	if (components_.find(type) == components_.end())
		return nullptr;

	return static_cast<T*>(components_[type]);
}
