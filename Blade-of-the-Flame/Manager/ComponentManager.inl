#include "ComponentManager.h"

#include <iostream>
#include <type_traits>	// std::is_base_of<Base, Derived>
#include "../GameObject/GameObject.h"

template<typename T>
template<typename U>
inline U* ComponentManager<T>::CreateComponent(GameObject* owner)
{
	if (std::is_base_of<T, U>::value)
	{
		components_.emplace_back(new U(owner));
		return static_cast<U*>(components_.back().get());
	}
	else
	{
		std::cerr << "[ERROR] ComponentManager::CreateComponent " << typeid(T).name() <<
			" is not a base class of " << typeid(U).name() << std::endl;
		return nullptr;
	}
}

template <typename T>
inline void ComponentManager<T>::UpdateComponent()
{
	for (auto it = components_.begin(); it != components_.end(); ++it)
		(*it)->Update();
}

template <typename T>
inline void ComponentManager<T>::DeleteComponent(T* const comp)
{
	for (auto it = components_.begin(); it != components_.end(); ++it)
	{
		if (it->get() == comp)
		{
			components_.erase(it);
			return;
		}
	}
}

template <typename T>
inline void ComponentManager<T>::Clear()
{
	components_.clear();
}