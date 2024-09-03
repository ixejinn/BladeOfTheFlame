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
	{
		if ((*it)->GetOwner()->active_)
			(*it)->Update();
	}
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

template<typename T>
inline void ComponentManager<T>::SwapComponent(T* const compA, T* const compB)
{
	auto itA = components_.begin();
	auto itB = components_.begin();
	bool bA = false, bB = false;

	for (auto it = components_.begin(); it != components_.end(); ++it)
	{
		if (it->get() == compA)
		{
			itA = it;
			bA = true;
		}
		else if (it->get() == compB)
		{
			itB = it;
			bB = true;
		}

		if (bA && bB)
			break;
	}

	components_.splice(itA, components_, itB);
}

template <typename T>
inline void ComponentManager<T>::Clear()
{
	components_.clear();
}