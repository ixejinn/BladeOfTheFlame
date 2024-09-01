#include "GameObject.h"

#include <iostream>
#include "../Component/RigidBody.h"
#include "../Manager/MonsterManager.h"

GameObject::~GameObject()
{
    for (auto it = components_.begin(); it != components_.end(); ++it)
        (it->second)->RemoveFromManager();
}

void GameObject::SetActive(bool b)
{
    active_ = false;

    if (GetComponent<Monster>())
        MonsterManager::GetInstance().Release(this);
}

void GameObject::DeleteComponent(std::type_index type)
{
    if (components_.find(type) == components_.end())
    {
        std::cout << "GameObject::DeleteComponent Not exist" << std::endl;
        return;
    }

    components_.erase(type);
}