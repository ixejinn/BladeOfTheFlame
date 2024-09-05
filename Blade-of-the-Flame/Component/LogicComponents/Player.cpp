#include "Player.h"

#include <typeindex>
#include <string>
#include "AEVec2.h"
#include "AEGraphics.h"
#include "BaseAttack.h"
#include "../../Event/Event.h"
#include "../../Manager/EventManager.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Manager/SkillManager.h"
#include "../../Manager/GameStateManager.h"
#include "../../Utils/Utils.h"
#include "../../Utils/MathUtils.h"
#include "../../State/GameOver.h"

bool enablePrint;

#include "../LogicComponents/Skills/Meteor.h"
#include "../LogicComponents/Skills/Flame.h"

Player::Player(GameObject* owner) : LogicComponent(owner)
{
	timeStart_ = std::chrono::system_clock::now();

	//SkillManager::GetInstance().CooldownCountMelee = 1000;
	SkillManager::GetInstance().CooldownCountMeteor = 1000;
	SkillManager::GetInstance().CooldownCountFlame = 1000;
	/* Set Player component */
	owner_->AddComponent<BoxCollider>();
	owner_->AddComponent<CircleCollider>();
	owner_->AddComponent<Sprite>();
	owner_->AddComponent<PlayerController>();
	owner_->AddComponent<Audio>();

	trans_ = owner_->GetComponent<Transform>();
	trans_->SetScale({ 30, 100 });
	AEVec2 limit{ windowWidth, windowHeight };
	limit = limit * 4.f;
	trans_->SetLimit(limit);

	owner_->GetComponent<RigidBody>()->SetUseAcceleration(false);

	BoxCollider* boxCol = owner_->GetComponent<BoxCollider>();
	boxCol->SetLayer(Collider::P_AABB);
	boxCol->SetHandler(static_cast<EventEntity*>(this));

	CircleCollider* circleCol = owner_->GetComponent<CircleCollider>();
	circleCol->SetLayer(Collider::P_CIRCLE);
	circleCol->SetRadius(attractionRadius_);

	owner_->GetComponent<Sprite>()->SetColor({ 200, 200, 200 });

	PlayerController* pCtrl = owner_->GetComponent<PlayerController>();
	pCtrl->SetDashKey(AEVK_SPACE);
	pCtrl->MultiplyMoveSpeed(moveSpeed_);

	audio_ = owner_->GetComponent<Audio>();
	audio_->SetAudio("Assets/ore.mp3");
	audio_->SetLoop(false);
	audio_->SetPlaying(false);

	/* BASIC ATTACK GameObject */
	meleeAttack_ = GameObjectManager::GetInstance().CreateObject("playerMeleeAttack");
	meleeAttack_->AddComponent<MeleeAttack>();
	meleeAttack_->GetComponent<MeleeAttack>()->SetPlayer(owner_);

	Skills_Meteor = GameObjectManager::GetInstance().CreateObject("MeteorAttack");
	Skills_Meteor->AddComponent<Meteor>();
	Skills_Meteor->GetComponent<Meteor>()->SetPlayer(owner_);

	Skills_Flame = GameObjectManager::GetInstance().CreateObject("FlameAttack");
	Skills_Flame->AddComponent<Flame>();
	Skills_Flame->GetComponent<Flame>()->SetPlayer(owner_);

	curAttackMelee 	= meleeAttack_->GetComponent<MeleeAttack>();

	ParticleSystem::getPtr()->SetParticle(30, { 10, 10 }, 1000);
}

void Player:: RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void Player::Update()
{
	/* CHECK */
	// Level up
	if (exp_ >= maxExp_)
		LevelUp();

	if (hp_ < 6)
		enablePrint = true;

	// Death
	if (hp_ <= 0)
	{
		owner_->active_ = false;

		GameOver* newState = new GameOver();
		GameStateManager::GetInstance().ChangeState(newState);
		return;
	}

	/* SET CAMERA */
	AEVec2 pos = trans_->GetPosition();
	AEGfxSetCamPosition(pos.x, pos.y);

	/* ATTACK */
	//SkillManager::GetInstance().CooldownCountMelee += AEFrameRateControllerGetFrameTime();
	SkillManager::GetInstance().CooldownCountMeteor += AEFrameRateControllerGetFrameTime();
	SkillManager::GetInstance().CooldownCountFlame += AEFrameRateControllerGetFrameTime();

	static unsigned int cnt = 0;
	std::chrono::duration<double> dt = std::chrono::system_clock::now() - timeStart_;
	if (dt.count() >= curAttackMelee->GetCooldown() && AEInputCheckCurr(AEVK_LBUTTON))
	{
		audio_->SetPlaying(true);
		timeStart_ = std::chrono::system_clock::now();

		curAttackMelee->AttackObject();
		cnt = 0;
	}
	else if (cnt >= 2)
		GameObjectManager::GetInstance().GetObjectA("playerMeleeAttack")->active_ = false;
	cnt++;

	if(curAttack_ == nullptr)
	{
		SkillManager::GetInstance().KeyCheck();
		SkillManager::GetInstance().SetSkillType(owner_->GetComponent<Player>()->level_);
		//if (AEInputCheckCurr(AEVK_LBUTTON)
		//	&& meleeAttack_->GetComponent<MeleeAttack>()->GetCooldown()
		//	<= SkillManager::GetInstance().CooldownCountMelee
		//	&& SkillManager::GetInstance().type == cScorching)
		//{
		//	curAttack_ = meleeAttack_->GetComponent<MeleeAttack>();
		//	curAttack_->On();
		//}
		if (AEInputCheckCurr(AEVK_LBUTTON)
			&& Skills_Flame->GetComponent<Flame>()->GetCooldown()
			<= SkillManager::GetInstance().CooldownCountFlame
			&& SkillManager::GetInstance().type == cFlame)
		{
			curAttack_ = Skills_Flame->GetComponent<Flame>();
			curAttack_->On();
		}
		if (AEInputCheckCurr(AEVK_LBUTTON)
			&& Skills_Meteor->GetComponent<Meteor>()->GetCooldown()
			<= SkillManager::GetInstance().CooldownCountMeteor
			&& SkillManager::GetInstance().type == cMeteor)
		{
			curAttack_ = Skills_Meteor->GetComponent<Meteor>();
			curAttack_->On();
		}
	}

	/* NEXT STAGE */
	static bool callBoss = true;
	if (getCompass_ && findAltar_ && callBoss)
	{
		std::cout << "Next stage!!" << std::endl;
		NextStageEvent* event = new NextStageEvent();
		event->from_ = owner_;
		EventManager::GetInstance().AddEvent(event);
		callBoss = false;
	}
}

void Player::LoadFromJson(const json& data)
{
}

json Player::SaveToJson()
{
	return json();
}

void Player::OnEvent(BaseEvent* event)
{
	std::type_index eventType = std::type_index(typeid(*event));

}

void Player::OnCollision(CollisionEvent* event)
{
	FlameAltar* altar = event->from_->GetComponent<FlameAltar>();
	if (altar)
	{
		if (getCompass_)
			findAltar_ = true;
	}
		
}

void Player::LevelUp()
{
	if (level_ >= maxLevel_)
		return;

	level_++;

	maxExp_ += int(maxExp_ * expRequirement_ / 100);
	exp_ = 0;

	ParticleSystem::getPtr()->Update();

	maxHp_ += int(maxHp_ * hpGrowthRate_ / 100);
	hp_ = maxHp_;
}

void Player::AddHp(int hp)
{
	std::cout << hp_ << " ";
	hp_ += hp;
	std::cout << hp_ << std::endl;
	
	if (hp_ > maxHp_)
		hp_ = maxHp_;
}

void Player::AddExp(int exp)
{
	exp_ += exp;
}

ComponentSerializer* Player::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Player>())
		std::cout << "Transform::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Player>();
}
