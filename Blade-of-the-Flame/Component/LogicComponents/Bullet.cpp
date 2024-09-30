#include <iostream>

#include "Bullet.h"
#include "../../Event/Event.h"
#include "../../Utils/MathUtils.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Component/AnimationComp.h"

BulletComp::BulletComp(GameObject* owner) : LogicComponent(owner), unitDir()
{
    bulletSpeed_ = 100.f;
    bulletDmg_ = 0.f;
    time = 0.f;
    owner_->AddComponent<BoxCollider>();
    owner_->AddComponent<AnimationComp>();
    owner_->AddComponent<Sprite>();

    BoxCollider* col = owner_->GetComponent<BoxCollider>();

    col->SetType(Collider::OBB_TYPE);
    col->SetLayer(Collider::E_ATTACK);
    col->SetHandler(static_cast<EventEntity*>(this));

    owner_->AddComponent<AnimationComp>();
    owner_->GetComponent<AnimationComp>()->AddAnimation("BossPhase1");

    owner_->AddComponent<Sprite>();
    owner_->GetComponent<Transform>()->SetScale({ 200, 200 });
    
    for (int i = 0; i < 19; i++)
    {
        std::string anim = "Assets/boss1_Anime/Atk/phase2ATK/phase1_" + std::to_string(i) + ".png";

        owner_->GetComponent<AnimationComp>()->AddDetail(anim, "BossPhase1");
    }
    /*for (int i = 18; i >= 0; i--)
    {
        std::string anim = "Assets/boss1_Anime/Atk/phase2ATK/phase1_" + std::to_string(i) + ".png";

        owner_->GetComponent<AnimationComp>()->AddDetail(anim, "BossPhase1");
    }*/

    owner_->GetComponent<AnimationComp>()->SetTerm(50);

    owner_->GetComponent<AnimationComp>()->ChangeAnimation("BossPhase1");

    player = GameObjectManager::GetInstance().GetObjectA("player");

    boss1 = GameObjectManager::GetInstance().GetObjectA("boss1");
    boss2 = GameObjectManager::GetInstance().GetObjectA("boss2");

    col->SetScale({ 0.4f, 0.4f });
    col->SetCenter({ 0.f, -0.2f });
}

void BulletComp::Update()
{	
    //boss2 test
    time += 0.1f;
    //CurveBullet();

    //DownBullet();

    CircleBullet();

    //RigidBody* bulletRigd = owner_->GetComponent<RigidBody>();
    //bulletRigd->AddVelocity(unitDir * bulletSpeed_);
}

void BulletComp::OnEvent(BaseEvent* event)
{

}

void BulletComp::OnCollision(CollisionEvent* event)
{
    Player* player = event->from_->GetComponent<Player>();
    if (check_ && player)
    {
        player->AddHp(int(-bulletDmg_));
        check_ = false;
    }
}

void BulletComp::RemoveFromManager()
{
    ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void BulletComp::FireBullet()
{
    Transform* bulletTrans = owner_->GetComponent<Transform>();
    RigidBody* bulletRigd = owner_->GetComponent<RigidBody>();

    Transform* playerTrans = player->GetComponent<Transform>();

    bulletTrans->SetPosition(boss1->GetComponent<Transform>()->GetPosition());

    AEVec2 dir = playerTrans->GetPosition() - bulletTrans->GetPosition();

    AEVec2Normalize(&unitDir, &dir);

    bulletRigd->AddVelocity(unitDir * bulletSpeed_);
}

void BulletComp::BarrageBullet(bool _bool = false)
{
    returnBullet = _bool;

    Transform* bulletTrans = owner_->GetComponent<Transform>();
    RigidBody* bulletRigd = owner_->GetComponent<RigidBody>();

    bulletTrans->SetPosition(boss1->GetComponent<Transform>()->GetPosition());

    bulletRigd->AddVelocity(unitDir * bulletSpeed_);
}

void BulletComp::DownBullet()
{
    Transform* playerTrans = player->GetComponent<Transform>();
    Transform* bulletTrans = owner_->GetComponent<Transform>();
    RigidBody* bulletRigd  = owner_->GetComponent<RigidBody>();
    
    AEVec2 playerPos;
    playerPos.x = playerTrans->GetPosition().x;
    playerPos.y = playerTrans->GetPosition().y;
   
    bulletTrans->SetPosition(playerPos.x, bulletTrans->GetPosition().y);

    bulletRigd->AddVelocity(0, -bulletSpeed_);

    //¸ØÃß´Â°Å
}

void BulletComp::CurveBullet()
{
    Transform* bulletTrans = owner_->GetComponent<Transform>();
    
    AEVec2 currentBulletPos;
    AEVec2 Boss2Pos  = boss2->GetComponent<Transform>()->GetPosition();
    AEVec2 playerPos = player->GetComponent<Transform>()->GetPosition();
   
    float angle = atan2(playerPos.y - Boss2Pos.y, playerPos.x - Boss2Pos.x);
    float radian = ((time * PI / 180) * 100);

    float bulletSpeed = 100.f;

    AEVec2 direction;
    direction.x = cos(angle) * bulletSpeed;
    direction.y = sin(angle) * bulletSpeed;

    currentBulletPos.x = Boss2Pos.x + direction.x * time;
    currentBulletPos.y = Boss2Pos.y + direction.y * time + sin(radian) * 100;

    unitDir = currentBulletPos;
    
    //1. x = time * xspeed, y = sin(radian)*y speed
    float x = time * bulletSpeed;
    float y = sin(radian) * bulletSpeed;

    //2. x, y rotation angle
    float rotated_x = cos(angle) * x - sin(angle) * y;
    float rotated_y = sin(angle) * x + cos(angle) * y;

    //3. bosspos + (x,y)
    float trans_x = Boss2Pos.x + rotated_x;
    float trans_y = Boss2Pos.y + rotated_y;

    //4. pos = (3)
    unitDir.x = trans_x;
    unitDir.y = trans_y;
    
    bulletTrans->SetPosition(unitDir);  
}

void BulletComp::CircleBullet()
{
    Transform* bulletTrans = owner_->GetComponent<Transform>();

    AEVec2 Boss2Pos  = boss2->GetComponent<Transform>()->GetPosition();
    AEVec2 playerPos = player->GetComponent<Transform>()->GetPosition();
    
    float radian = ((time * PI / 180) * 100);

    float bulletSpeed = 100.f;

    AEVec2 direction;
    direction.x = cos(radian) * bulletSpeed;
    direction.y = sin(radian) * bulletSpeed;

    unitDir = direction;

    bulletTrans->SetPosition(unitDir);
}

void BulletComp::LoadFromJson(const json&)
{

}

json BulletComp::SaveToJson()
{
    return json();
}

ComponentSerializer* BulletComp::CreateComponent(GameObject* owner)
{
    if (!owner->AddComponent<BulletComp>())
        std::cout << "BulletComp::CreateComponent() Component already exists" << std::endl;

    return owner->GetComponent<BulletComp>();
}
