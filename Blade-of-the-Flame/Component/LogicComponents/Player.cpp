#include "Player.h"

#include <typeindex>
#include <string>
#include "AEVec2.h"
#include "AEGraphics.h"
#include "BaseAttack.h"
#include "../../Event/Event.h"
#include "../../Manager/EventManager.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Manager/GameStateManager.h"
#include "../../Utils/Utils.h"
#include "../../Utils/MathUtils.h"
#include "../../State/GameOver.h"
#include "../AnimationComp.h"
#include "../LogicComponents/Skills/Meteor.h"
#include "../LogicComponents/Skills/Flame.h"
#include "../../Manager/Camera.h"

void Player::SetAnimation()
{
	ani_->AddAnimation("Idle");
	for (int i = 1; i <= 18; i++)
	{
		std::string name = "Assets/Player_anime/Idle/row-1-column-" + std::to_string(i) + ".png";
		ani_->AddDetail(name, "Idle");
	}

	ani_->AddAnimation("Run");
	for (int i = 1; i <= 24; i++)
	{
		std::string name = "Assets/Player_anime/run/row-1-column-" + std::to_string(i) + ".png";
		ani_->AddDetail(name, "Run");
	}

	ani_->AddAnimation("Attack");
	for (int i = 1; i <= 12; i++)
	{
		std::string name = "Assets/Player_anime/Atk/row-1-column-" + std::to_string(i) + ".png";
		ani_->AddDetail(name, "Attack");
	}

	ani_->ChangeAnimation("Idle");
	ani_->SetTerm(300);
}


Player::Player(GameObject* owner) : LogicComponent(owner)
{
	level_ = 1;
	/* Set Player component */
	owner_->AddComponent<CircleCollider>();
	owner_->AddComponent<BoxCollider>();
	owner_->AddComponent<PlayerController>();
	owner_->AddComponent<Audio>();
	owner_->AddComponent<AnimationComp>();

	trans_ = owner_->GetComponent<Transform>();
	trans_->SetScale({ windowWidth / 13.f, windowWidth / 13.f });

	owner_->GetComponent<RigidBody>()->SetUseAcceleration(false);

	BoxCollider* boxCol = owner_->GetComponent<BoxCollider>();
	boxCol->SetLayer(Collider::P_AABB);
	boxCol->SetHandler(static_cast<EventEntity*>(this));
	boxCol->SetScale({ 0.25, 0.4 });
	boxCol->SetCenter({ 0.f, -0.04f });

	CircleCollider* circleCol = owner_->GetComponent<CircleCollider>();
	circleCol->SetLayer(Collider::P_CIRCLE);
	circleCol->SetRadius(50.f);

	pCtrl_ = owner_->GetComponent<PlayerController>();
	pCtrl_->SetDashKey(AEVK_SPACE);
	pCtrl_->MultiplyMoveSpeed(moveSpeed_);

	audio_ = owner_->GetComponent<Audio>();
	audio_->SetAudio("Assets/ore.mp3");
	audio_->SetLoop(false);
	audio_->SetPlaying(false);

	owner_->GetComponent<Sprite>()->SetLocalPos(0.15f, 0.f);
	ani_ = owner_->GetComponent<AnimationComp>();
	SetAnimation();

	sp_ = owner_->GetComponent<Sprite>();

	/* BASIC ATTACK GameObject */
	melee_Attack = GameObjectManager::GetInstance().CreateObject("MeleeAttack");
	melee_Attack->AddComponent<MeleeAttack>();
	melee_Attack->GetComponent<MeleeAttack>()->SetPlayer(owner_);

	/* Special ATTACK GameObject */
	//meteor_Attack = GameObjectManager::GetInstance().CreateObject("MeteorAttack");
	//meteor_Attack->AddComponent<Meteor>();
	//meteor_Attack->GetComponent<Meteor>()->SetPlayer(owner_);

	//----------------------------------//
	curAttack_ = melee_Attack->GetComponent<MeleeAttack>();
}

void Player::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void Player::Update()
{
	/* CHECK */
	// Level up
	if (exp_ >= maxExp_)
		LevelUp();

	// Death
	static int preHp = hp_;
	if (hp_ <= 0)
	{
		owner_->active_ = false;

		GameOver* newState = new GameOver();
		GameStateManager::GetInstance().ChangeState(newState);
		return;
	}

	// MOUSE BUTTON & State
	static State preState = IDLE;
	State curState = IDLE;
	Direction curDir = dir_;
	bool lBtn = false;
	if (AEInputCheckCurr(AEVK_LBUTTON))
	{
		lBtn = true;
		curState = ATTACK;
	}
	else if (hp_ < preHp)
	{
		curState = HURT;
		preHp = hp_;
	}
	else if (pCtrl_->GetMoveState())
	{
		curState = RUN;
		curDir = pCtrl_->GetMoveDir();
	}
	else
		curState = IDLE;

	/* ATTACK */
	if (1 <= level_ && level_ < 4)
	{
		meleeCool += AEFrameRateControllerGetFrameTime();
		if (SkillGage >= 100)
		{
			//쉴드스킬
		}
		else
		{
			curAttack_ = melee_Attack->GetComponent<MeleeAttack>();
		}
	}
	else if (4 <= level_ && level_ < 7)
	{
		flameCool += AEFrameRateControllerGetFrameTime();
		if (SkillGage >= 100)
		{
			//장판스킬
		}
		else
		{
			if (AEInputCheckCurr(AEVK_LBUTTON) && flameCool >= 1)
			{
				GameObject* flame_Attack = nullptr;
				flame_Attack = GameObjectManager::GetInstance().CreateObject("FlameAttack" + std::to_string(count));
				count++;
				flame_Attack->AddComponent<Flame>();
				flame_Attack->GetComponent<Flame>()->SetPlayer(owner_);
				curAttack_ = flame_Attack->GetComponent<Flame>();
				curAttack_->On();
			}
		}
	}
	else if (7 <= level_ && level_ < 10)
	{
		//더블 플레임
		//메테오
	}
	else
	{
		//관통 더블 플레임
		// 파이어 버블
	}

	if (curAttack_ == melee_Attack->GetComponent<MeleeAttack>() &&
		curAttack_->GetCooldown() <= meleeCool && 
		AEInputCheckCurr(AEVK_LBUTTON))
	{
		audio_->SetPlaying(true);
		curAttack_->AttackObject();
		meleeCool = 0;
	}

	/* NEXT STAGE */
	static bool callBoss = true;
	if (getCompass_ && findAltar_ && callBoss)
	{
		std::cout << "Next stage!!" << std::endl;
		SpawnBossEvent* event = new SpawnBossEvent();
		event->from_ = owner_;
		EventManager::GetInstance().AddEvent(event);
		callBoss = false;
	}

	/* SET ANIMATION */
	if (dir_ != curDir)
		trans_->SetFlip();

	if (curState == ATTACK)
	{
		ani_->ChangeAnimation("Attack");
		ani_->SetTerm(50);
	}
	else if ((preState == ATTACK && ani_->CurrentAnimationOver()) || preState != ATTACK)
	{
		if (curState == RUN)
		{
			ani_->ChangeAnimation("Run");
			ani_->SetTerm(60);
		}
		else if (curState == HURT)
			sp_->SetColor({ 255, 0, 0 });
		else
		{
			ani_->ChangeAnimation("Idle");
			ani_->SetTerm(300);
		}
	}

	if (curState != HURT && preState != HURT)
		sp_->SetColor({ 0, 0, 0 });

	//std::cout << dir_ << " " << curDir << std::endl;
	dir_ = curDir;
	preState = curState;
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
	ParticleSystem::getPtr()->Update();

	maxExp_ += int(maxExp_ * expRequirement_ / 100);
	exp_ = 0;

	maxHp_ += int(maxHp_ * hpGrowthRate_ / 100);
	hp_ = maxHp_;

	if (level_ >= maxLevel_)
		return;

	level_++;

	LevelUpEvent* event = new LevelUpEvent();
	event->from_ = owner_;
	event->level = level_;
	EventManager::GetInstance().AddEvent(event);
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
