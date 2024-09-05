#pragma once
#include <list>
#include <memory>

class GameObject;

/**
* @brief	ComponentManager는 Component의 생성과 해제에만 관여하므로 GameObject에 Component 부착은 직접 해야 함
* @tparam T	EngineComponent, GraphicsComponent, ...
*/
template <typename T>
class ComponentManager
{
private:
	std::list<std::unique_ptr<T>> components_;

	ComponentManager() = default;
	~ComponentManager()
	{
		int i;
	}

	ComponentManager(const ComponentManager&) = delete;
	ComponentManager& operator =(const ComponentManager&) = delete;
	ComponentManager(ComponentManager&&) = delete;
	ComponentManager& operator =(ComponentManager&&) = delete;

public:
	static ComponentManager& GetInstance()
	{
		static ComponentManager instance;
		return instance;
	}

	// @brief	GameObject::AddComponent()는 Component 생성 + GameObject에 부착이 한번에 가능하므로 추천됨
	// @tparam U	Transform, Sprite, ...
	template <typename U>
	U* CreateComponent(GameObject* owner);

	void UpdateComponent();
	void DeleteComponent(T* const comp);

	void SwapComponent(T* const compA, T* const compB);
	void ToBack(T* const compA);

	void Clear();
};

#include "ComponentManager.inl"