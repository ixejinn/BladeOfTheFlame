#include "Registry.h"

#include <iostream>
#include "../Component/Audio.h"
#include "../Component/Transform.h"
#include "../Component/RigidBody.h"
#include "../Component/Sprite.h"
#include "../Component/LogicComponents/PlayerController.h"

Registry::Registry()
{
    //// TODO: componentMap에 컴포넌트 생성 함수 추가
    componentMap.insert({ Transform::TypeName, &Transform::CreateComponent });
    componentMap.insert({ RigidBody::TypeName, &RigidBody::CreateComponent });
    componentMap.insert({ Sprite::TypeName, &Sprite::CreateComponent });
    componentMap.insert({ Audio::TypeName, &Audio::CreateComponent });
    componentMap.insert({ PlayerController::TypeName, &PlayerController::CreateComponent });
}

ComponentSerializer* Registry::CreateComponent(const std::string& typeName, GameObject* owner)
{
    if (componentMap.find(typeName) == componentMap.end())
    {
        std::cerr << "Registry::CreateComponent() Invalid component type " << typeName << std::endl;
        return nullptr;
    }

    return componentMap[typeName](owner);
}
