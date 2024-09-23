#include "Boss2.h"
#include <typeindex>

#include "../../Event/Event.h"
#include "../../Utils/MathUtils.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Manager/EventManager.h"
#include "../../Manager/GameStateManager.h"
#include "../../Utils/RandomEngine.h"
#include "../../State/GameClear.h"
#include "../../Component/AnimationComp.h"

Boss2::Boss2(GameObject* owner):LogicComponent(owner)
{
    player = GameObjectManager::GetInstance().GetObjectA("player");
    owner_->AddComponent<BoxCollider>();
    owner_->AddComponent<Sprite>();
    owner_->AddComponent<AnimationComp>();
    scale = { 300, 300 };

    owner_->GetComponent<Transform>()  ->SetScale   (scale);
    owner_->GetComponent<Transform>()  ->SetPosition({ 400, 400 });
    owner_->GetComponent<BoxCollider>()->SetScale   ({ 0.4f, 0.8f });

    AnimationComp* bossAnim = owner_->GetComponent<AnimationComp>();

    bossAnim->AnimationLoop(0, 3, "Assets/boss2_Anime/boss2_", "walk");
    bossAnim->ChangeAnimation("walk");

    owner_->GetComponent<Transform>()->SetScale(scale);
    owner_->GetComponent<Transform>()->SetPosition({ 400,400 });
}

void Boss2::Update()
{
    BossState();
}

void Boss2::RemoveFromManager()
{
    ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void Boss2::OnEvent(BaseEvent* event)
{

}

void Boss2::OnCollision(CollisionEvent* event)
{

}

GameObject* Boss2::CreateBulletObj()
{
    std::string unique_bullet_name = "bullet" + std::to_string(bullet.size());
    GameObject* addBullet = GameObjectManager::GetInstance().CreateObject(unique_bullet_name);
    bullet.push_back(addBullet);
    addBullet->AddComponent<BulletComp>();
    return addBullet;
}

void Boss2::BossState()
{
    AnimationComp* bossAnim = owner_->GetComponent<AnimationComp>();
    Transform* bossScale = owner_->GetComponent<Transform>();

    bossAnim->SetTerm(150);
    bossAnim->ChangeAnimation("walk");
}

void Boss2::BaseChase()
{

}

void Boss2::Phase1()
{

}

float Boss2::Dot(const AEVec2& vec1, const AEVec2& vec2)
{

    return 0.0f;
}

bool Boss2::Flip(AEVec2 flip)
{

    return false;
}


void Boss2::ReserveDmg(int dmg)
{

}

void Boss2::LoadFromJson(const json&)
{

}

json Boss2::SaveToJson()
{
    return json();
}


ComponentSerializer* Boss2::CreateComponent(GameObject* owner)
{
    return nullptr;
}

