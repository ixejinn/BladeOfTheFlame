#include "Boss1.h"

#include <typeindex>
#include "../../Event/Event.h"
#include "../../Utils/MathUtils.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Manager/EventManager.h"
#include "../../Manager/GameStateManager.h"
#include "../../Utils/RandomEngine.h"
#include "../../State/GameClear.h"
#include "../../Component/AnimationComp.h"

Boss1::Boss1(GameObject* owner) : LogicComponent(owner)
{
    player = GameObjectManager::GetInstance().GetObjectA("player");

    owner_->AddComponent<BoxCollider>();
    owner_->AddComponent<Sprite>();
    owner_->AddComponent<AnimationComp>();

    Transform* trans_ = owner_->GetComponent<Transform>();
    //trans_->SetScale({ 200, 200 });
    //trans_->SetPosition({ 400,400 });

    BoxCollider* col = owner_->GetComponent<BoxCollider>();
    col->SetLayer(Collider::E_BODY);
    col->SetHandler(static_cast<EventEntity*>(this));

    timeStart_ = std::chrono::system_clock::now();

    hp_         = 500;
    maxHp_      = 500;
    moveSpeed_  = 5;
    chaseSpeed_ = 30;
    baseDmg_    = 5;
    skillDmg_   = 10;
    range_      = 1.5;
    
    scale = { 900, 900 };

    nomalphaseTime_ = 0.0;
    DelayTime_      = 0.0;

    phase1Count_ = 0;
    phase2Count_ = 0;
    shootCount_  = 0;

    phase1_cool = 0;
    phase2_cool = 0;
    phase3_cool = 0;

    current_state = _baseChase;

    phase1On = false;
    phase2On = false;
    phase3On = false;

    baseChase = true;
    needShoot = true;
    isAction  = true;

    owner_->active_ = false;
    EventManager::GetInstance().RegisterEntity(std::type_index(typeid(SpawnBossEvent)), static_cast<EventEntity*>(this));

    AnimationComp* bossAnim = owner_->GetComponent<AnimationComp>();
    
    bossAnim->AnimationLoop(0, 16, "Assets/boss1_Anime/walk/walk", "walk");
    bossAnim->AnimationLoop(0, 16, "Assets/boss1_Anime/Idle/Idle", "Idle");
    bossAnim->AnimationLoop(0, 5,  "Assets/boss1_Anime/Atk/phase2ATK/phase1_", "Attack");

    bossAnim->ChangeAnimation("walk");
    owner_->GetComponent<Transform>()->SetScale(scale);
    owner_->GetComponent<Transform>()->SetPosition({ 400,400 });

    col->SetScale({ 0.22f, 0.45f });
    col->SetCenter({ 0.f, -0.15f });
}

void Boss1::Update()
{
    if (hp_ <= 0)
    {
        owner_->active_ = false;
        bullet.clear();

        GameClear* newState = new GameClear();
        GameStateManager::GetInstance().ChangeState(newState);
        return;
    }

    BossState();
}

void Boss1::RemoveFromManager()
{
    ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void Boss1::OnEvent(BaseEvent* event)
{
    AEVec2 playerPos = player->GetComponent<Transform>()->GetPosition();
    playerPos.x += 200;
    owner_->GetComponent<Transform>()->SetPosition(playerPos);
    // ��� �� ���̱�
    owner_->active_ = true;
}

void Boss1::OnCollision(CollisionEvent* event)
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

void Boss1::ReserveDmg(int dmg)
{
    hp_ -= dmg;
}

GameObject* Boss1::CreateBulletObj()
{
    std::string unique_bullet_name = "bullet" + std::to_string(bullet.size());
    GameObject* addBullet = GameObjectManager::GetInstance().CreateObject(unique_bullet_name);
    bullet.push_back(addBullet);
    addBullet->AddComponent<BulletComp>();

    return addBullet;
}

void Boss1::BossState()
{
    if (current_state == _baseChase)
    {
        BaseChase();
    }
    else if (current_state == _fastChase)
    {
        if (!isAction) Phase1();
    }
    else if (current_state == _rangeAttack)
    {
        if (!isAction) Phase2();
    }
    else if (current_state == _barrage)
    {
        if (!isAction) Phase3();
    }
}

void Boss1::BaseChase()
{
    AnimationComp* bossAnim  = owner_->GetComponent<AnimationComp>();
    Transform*     bossScale = owner_->GetComponent<Transform>();
    //�ִϸ��̼� �����ϴ� �Լ�

    if (nomalphaseTime_ < 100)
    {
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
        nomalphaseTime_ += 1;
    }
    else
    {
        isAction = false;
        nomalphaseTime_ = 0;
        current_state   = _fastChase; 
    }
}

void Boss1::Phase1()
{
    Transform* bossScale = owner_->GetComponent<Transform>();
    AnimationComp* bossAnim = owner_->GetComponent<AnimationComp>();

    bossAnim->SetTerm(50);
    bossAnim->ChangeAnimation("walk");

    if (DelayTime_ < 5)
    {

        Transform* bossTrans = owner_->GetComponent<Transform>();
        RigidBody* bossRb = owner_->GetComponent<RigidBody>();
        
        AEVec2     playerPos = player->GetComponent<Transform>()->GetPosition();
        AEVec2	   bossPos = bossTrans->GetPosition();
        
        AEVec2	   chaseVec = playerPos - bossPos;
        AEVec2	   unitChaseVec;
        
        AEVec2Normalize(&unitChaseVec, &chaseVec);
        
        bossRb->AddVelocity(unitChaseVec * chaseSpeed_);

        if (Flip(chaseVec))
        {
            bossScale->SetScale(scale);
        }
        else
        {
            bossScale->SetScale({ scale.x * -1, scale.y });
        }

        DelayTime_   += 0.1f;
    }
    else if (phase1Count_ > 3)
    {
        current_state = _rangeAttack;
        phase1Count_ = 0;
    }
    else if (phase2On)
    {
        current_state = _barrage;
        phase2On = false;
    }
    else
    {
        phase1Count_ += 1;
        DelayTime_    = 0;
        current_state = _baseChase;
    }
}

void Boss1::Phase2()
{
    Transform* bossScale = owner_->GetComponent<Transform>();

    AnimationComp* bossAnim = owner_->GetComponent<AnimationComp>();

    bossAnim->SetTerm(200);
    bossAnim->ChangeAnimation("Idle");

    if (needShoot && shootCount_ < 3)
    {

        if (DelayTime_ > 1)
        {
            CreateBulletObj()->GetComponent<BulletComp>()->FireBullet();
            DelayTime_   = 0;
            shootCount_ += 1;
        }
        DelayTime_  += 0.1f;
    }
    else if (shootCount_ > 2)
    {
        phase2_cool += 1;
    }
    if (phase2_cool > 30)
    {
        shootCount_   = 0;
        phase2_cool   = 0;
        phase2Count_ += 1;
    }
    else if (phase2Count_ > 3)
    {
        shootCount_  = 0;
        phase2_cool  = 0;
        phase2Count_ = 0;
        phase2On = true;
        current_state = _baseChase;
    }
}

void Boss1::Phase3()
{
    AnimationComp* bossAnim = owner_->GetComponent<AnimationComp>();
    Transform* bossScale = owner_->GetComponent<Transform>();

    bossAnim->SetTerm(200);
    bossAnim->ChangeAnimation("Idle");

    if (phase3_cool < 150)
    {
        phase3_cool += 1;
        return;
    }
    phase3_cool = 0;

    std::vector<f32> dir_x(4);
    std::vector<f32> dir_y(4);

    int count = 15;

    float intervalAngle = 360.f / count;


    for (int i = 0; i < count; i++)
    {
        GameObject* temp = CreateBulletObj();

        float angle = intervalAngle * i;

        float radian = angle * PI / 180.0f;

        AEVec2 tempDir;

        tempDir.x = cos(radian);
        tempDir.y = sin(radian);

        temp->GetComponent<BulletComp>()->unitDir = tempDir;
        temp->GetComponent<BulletComp>()->BarrageBullet(false);

    }
    current_state = _baseChase;

    phase3On = false;
    baseChase = true;
}

void Boss1::Phase4()
{
    if (phase3_cool < 150)
    {
        phase3_cool += 1;
        return;
    }

    phase3_cool = 0;

    std::vector<f32> dir_x(4);
    std::vector<f32> dir_y(4);

    int count = 30;

    float intervalAngle = 360.f / count;


    for (int i = 0; i < count; i++)
    {
        GameObject* temp = CreateBulletObj();

        float angle = intervalAngle * i;

        float radian = angle * PI / 180.0f;

        AEVec2 tempDir;

        tempDir.x = cos(radian);
        tempDir.y = sin(radian);

        temp->GetComponent<BulletComp>()->unitDir = tempDir;
        temp->GetComponent<BulletComp>()->BarrageBullet(true);
    }
    needShoot = false;
}

float Boss1::Dot(const AEVec2& vec1, const AEVec2& vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

bool Boss1::Flip(AEVec2 flip)
{
    AEVec2 vec2 = { 1.0f, 0.0f };

    float flipCheck = Dot(flip, vec2);

    return flipCheck > 0;
}

void Boss1::LoadFromJson(const json&)
{

}

json Boss1::SaveToJson()
{
    return json();
}

ComponentSerializer* Boss1::CreateComponent(GameObject* owner)
{
    return nullptr;
}
