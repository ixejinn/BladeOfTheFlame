#include "Boss1.h"
#include "../../Utils/MathUtils.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Component/AnimationComp.h"

Boss1::Boss1(GameObject* owner) : BossComp(owner)
{
    hp_         = 500;
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

    owner_->AddComponent<Transform>();
    owner_->AddComponent<RigidBody>();
    owner_->AddComponent<AnimationComp>();
    
    AnimationComp* bossAnim = owner_->GetComponent<AnimationComp>();
    owner_->AddComponent<Sprite>();
    
    bossAnim->AnimationLoop(0, 16, "Assets/boss1_Anime/walk/walk", "walk");
    bossAnim->AnimationLoop(0, 16, "Assets/boss1_Anime/Idle/Idle", "Idle");
    bossAnim->AnimationLoop(0, 5,  "Assets/boss1_Anime/Atk/phase2ATK/phase1_", "Attack");

    bossAnim->ChangeAnimation("walk");
    owner_->GetComponent<Transform>()->SetScale(scale);
    owner_->GetComponent<Transform>()->SetPosition({ 400,400 });
}

void Boss1::Update()
{
    BossState();
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
    //애니메이션 실행하는 함수

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
        DelayTime_  += 0.1;
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

    int count = 30;

    float intervalAngle = 360 / count;


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

    float intervalAngle = 360 / count;


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
