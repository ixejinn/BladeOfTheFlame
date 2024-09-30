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


//중간보스입니다

Boss2::Boss2(GameObject* owner) :LogicComponent(owner)
{
    hp_ = 0;
    maxHp_ = 0;
    moveSpeed_ = 5.f;
    chaseSpeed_ = 0.f;
    baseDmg_ = 0.f;
    skillDmg_ = 0.f;
    range_ = 0.f;
    isAction = false;

    player = GameObjectManager::GetInstance().GetObjectA("player");

    owner_->AddComponent<BoxCollider>();
    owner_->AddComponent<Sprite>();
    owner_->AddComponent<AnimationComp>();

    scale = { 300, 300 };

    owner_->GetComponent<Transform>()->SetScale(scale);
    owner_->GetComponent<Transform>()->SetPosition({ 400, 400 });
    owner_->GetComponent<BoxCollider>()->SetScale({ 0.4f, 0.8f });

    AnimationComp* bossAnim = owner_->GetComponent<AnimationComp>();

    bossAnim->AnimationLoop(0, 3, "Assets/boss2_Anime/boss2_", "walk");
    bossAnim->ChangeAnimation("walk");

    owner_->GetComponent<Transform>()->SetScale(scale);
    owner_->GetComponent<Transform>()->SetPosition({ 400,400 });
}

void Boss2::Update()
{
    BossState();
    
    if (AEInputCheckCurr(AEVK_Z))
    {
        isAction = true;
    }
    if(phase1Count_ < 1000)
    {
        Phase1();
        isAction = false;
    }
}

void Boss2::RemoveFromManager()
{
    ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void Boss2::OnEvent(BaseEvent* event)
{
    AEVec2 playerPos = player->GetComponent<Transform>()->GetPosition();

    playerPos.x += 200;
    owner_->GetComponent<Transform>()->SetPosition(playerPos);

    owner_->active_ = true;
}

void Boss2::OnCollision(CollisionEvent* event)
{
    Player* player = event->from_->GetComponent<Player>();
    if (player)
    {
        std::chrono::duration<double> dt = std::chrono::system_clock::now() - timeStart_;
        if (dt.count() >= cooldown_)
        {
            timeStart_ = std::chrono::system_clock::now();

            player->AddHp(int(-baseDmg_));
        }
        return;
    }

    MeleeAttack* melee = event->from_->GetComponent<MeleeAttack>();
    if (melee)
    {
        hp_ -= melee->GetDmg();

        RigidBody* rb = owner_->GetComponent<RigidBody>();
        AEVec2 velocity = rb->GetVelocity();
        rb->ClearVelocity();

        return;
    }
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

}

void Boss2::BaseChase()
{
    AnimationComp* bossAnim = owner_->GetComponent<AnimationComp>();
    Transform* bossScale = owner_->GetComponent<Transform>();

    bossAnim->SetTerm(150);
    bossAnim->ChangeAnimation("walk");

    Transform* bossTrans = owner_->GetComponent<Transform>();
    RigidBody* bossRb = owner_->GetComponent<RigidBody>();

    AEVec2     playerPos = player->GetComponent<Transform>()->GetPosition();
    AEVec2	   bossPos = bossTrans->GetPosition();

    AEVec2	   chaseVec = playerPos - bossPos;

    AEVec2	   unitChaseVec;

    AEVec2Normalize(&unitChaseVec, &chaseVec);

    bossRb->AddVelocity(unitChaseVec * moveSpeed_);

    if (Flip(chaseVec))
    {
        bossScale->SetScale(scale);
    }
    else
    {
        bossScale->SetScale({ scale.x * -1, scale.y });
    }
}

void Boss2::Phase1()//curveBullet
{
    AEVec2 boss2Pos = owner_->GetComponent<Transform>()->GetPosition();

    deltaTime_ += 0.1f;
    
    if (isAction != false)
    {
        GameObject* temp = CreateBulletObj();
        temp->GetComponent<Transform>()->SetPosition(boss2Pos);
        phase1Count_ += 1;
        isAction = true;
    }
}

void Boss2::Phase2()//downBullet
{
    if (isAction != false)
    {
        GameObject* temp = CreateBulletObj();
        Transform* pT = player->GetComponent<Transform>();
        AEVec2 _p;
        _p.x = pT->GetPosition().x;
        _p.y = pT->GetPosition().y + 150;
        temp->GetComponent<Transform>()->SetPosition(_p.x, _p.y);
        phase2Count_ += 1;
        isAction = true;
    }
}

void Boss2::Phase3() //CircleBullet
{
    AEVec2 boss2Pos = owner_->GetComponent<Transform>()->GetPosition();

    if (isAction != false)
    {
        GameObject* temp = CreateBulletObj();
        temp->GetComponent<Transform>()->SetPosition(boss2Pos);
        phase1Count_ += 1;
        isAction = true;
    }
}

float Boss2::Dot(const AEVec2& vec1, const AEVec2& vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

bool Boss2::Flip(AEVec2 flip)
{
    AEVec2 vec2 = { 1.0f, 0.0f };

    float flipCheck = Dot(flip, vec2);

    return flipCheck > 0;
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

