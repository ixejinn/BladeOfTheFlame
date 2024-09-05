#include "Player.h"

#include <typeindex>
#include <string>
#include "AEVec2.h"
#include "AEGraphics.h"
#include "../../Event/Event.h"
#include "../../Manager/EventManager.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Manager/GameStateManager.h"
#include "../../Utils/Utils.h"
#include "../../Utils/MathUtils.h"
#include "../../State/GameOver.h"
#include "../AnimationComp.h"

void Player::SetAnimation()
{
	ani_->AddAnimation("Idle");
	for (int i = 2; i < 5; i++)
	{
		std::string name = "Assets/Player_anime/Idle/image_" + std::to_string(i) + ".png";
		ani_->AddDetail(name, "Idle");
	}
	for (int i = 4; i >= 2; i--)
	{
		std::string name = "Assets/Player_anime/Idle/image_" + std::to_string(i) + ".png";
		ani_->AddDetail(name, "Idle");
	}
	ani_->SetTerm(500);

	ani_->ChangeAnimation("Idle");
}

Player::Player(GameObject* owner) : LogicComponent(owner)
{
	timeStart_ = std::chrono::system_clock::now();

	/* Set Player component */
	owner_->AddComponent<BoxCollider>();
	owner_->AddComponent<CircleCollider>();
	owner_->AddComponent<Sprite>();
	owner_->AddComponent<PlayerController>();
	owner_->AddComponent<Audio>();
	owner_->AddComponent<AnimationComp>();

	trans_ = owner_->GetComponent<Transform>();
	trans_->SetScale({ 45, 100 });
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

	PlayerController* pCtrl = owner_->GetComponent<PlayerController>();
	pCtrl->SetDashKey(AEVK_SPACE);
	pCtrl->MultiplyMoveSpeed(moveSpeed_);

	audio_ = owner_->GetComponent<Audio>();
	audio_->SetAudio("Assets/ore.mp3");
	audio_->SetLoop(false);
	audio_->SetPlaying(false);

	ani_ = owner_->GetComponent<AnimationComp>();
	SetAnimation();

	/* BASIC ATTACK GameObject */
	meleeAttack_ = GameObjectManager::GetInstance().CreateObject("playerMeleeAttack");
	meleeAttack_->AddComponent<MeleeAttack>();
	meleeAttack_->GetComponent<MeleeAttack>()->SetPlayer(owner_);
	//rangedAttack_ = GameObjectManager::GetInstance().CreateObject("playerRangedAttack");

	curAttack_ = meleeAttack_->GetComponent<MeleeAttack>();
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
	if (AEInputCheckCurr(AEVK_Q))
		readyMelee = !readyMelee;

	static unsigned int cnt = 0;
	std::chrono::duration<double> dt = std::chrono::system_clock::now() - timeStart_;
	if (dt.count() >= curAttack_->GetCooldown() && AEInputCheckCurr(AEVK_LBUTTON) && readyMelee)
	{
		audio_->SetPlaying(true);
		timeStart_ = std::chrono::system_clock::now();

		curAttack_->AttackObject();
		cnt = 0;
	}
	else if (cnt >= 2)
		GameObjectManager::GetInstance().GetObjectA("playerMeleeAttack")->active_ = false;

	cnt++;

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

	maxHp_ += int(maxHp_ * hpGrowthRate_ / 100);
	hp_ = maxHp_;
	
	LevelUpEvent* event = new LevelUpEvent();
	event->from_ = owner_;
	event->level = level_;
	EventManager::GetInstance().AddEvent(event);
}

void Player::AddHp(int hp)
{
	hp_ += hp;
	
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
