#include "Player.h"

#include <typeindex>
#include <string>
#include "AEGraphics.h"
#include "../../Event/Event.h"
#include "../../Manager/EventManager.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Manager/SkillManager.h"
#include "../../Utils/Utils.h"

#include "../LogicComponents/Skills/Meteor.h"
#include "../LogicComponents/Skills/Flame.h"

Player::Player(GameObject* owner) : LogicComponent(owner)
{
	SkillManager::GetInstance().CooldownCountMelee = 1000;
	SkillManager::GetInstance().CooldownCountMeteor = 1000;
	SkillManager::GetInstance().CooldownCountFlame = 1000;
	/* Set Player component */
	owner_->AddComponent<BoxCollider>();
	owner_->AddComponent<CircleCollider>();
	owner_->AddComponent<Sprite>();
	owner_->AddComponent<PlayerController>();
	//owner_->AddComponent<Audio>();
	owner_->AddComponent<Text>();

	BoxCollider* boxCol = owner_->GetComponent<BoxCollider>();
	boxCol->SetLayer(Collider::P_AABB);
	boxCol->SetHandler(static_cast<EventEntity*>(this));

	CircleCollider* circleCol = owner_->GetComponent<CircleCollider>();
	circleCol->SetLayer(Collider::P_CIRCLE);
	circleCol->SetRadius(attractionRadius_);

	PlayerController* pCtrl = owner_->GetComponent<PlayerController>();
	pCtrl->SetRotKeys(PlayerController::LEFT, AEVK_Q);
	pCtrl->SetRotKeys(PlayerController::RIGHT, AEVK_E);
	pCtrl->SetDashKey(AEVK_SPACE);

	trans_ = owner_->GetComponent<Transform>();
	trans_->SetScale({ 30, 100 });
	owner_->GetComponent<PlayerController>()->MultiplyMoveSpeed(moveSpeed_);
	owner_->GetComponent<RigidBody>()->SetUseAcceleration(false);
	owner_->GetComponent<Sprite>()->SetColor({ 200, 200, 200 });

	text_ = owner_->GetComponent<Text>();
	text_->SetFont("Assets/Roboto-Bold.ttf");
	text_->SetSize(1.f);
	text_->SetColor({ 255, 0, 0 });
	text_->SetPosition({ -0.05f, 0.1f });

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
}

void Player:: RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}
float delay = 5;
void Player::Update()
{
	/* CHECK */
	// Level up
	if (exp_ >= maxExp_)
		LevelUp();

	// Death
	if (hp_ <= 0)
	{
		std::cout << "Game over" << std::endl;
		GameOverEvent* event{ new GameOverEvent() };
		event->from_ = owner_;
		EventManager::GetInstance().AddEvent(event);
		owner_->active_ = false;
	}

	/* SET CAMERA */
	AEVec2 pos = trans_->GetPosition();
	AEGfxSetCamPosition(pos.x, pos.y);

	/* ATTACK */
	SkillManager::GetInstance().CooldownCountMelee += AEFrameRateControllerGetFrameTime();
	SkillManager::GetInstance().CooldownCountMeteor += AEFrameRateControllerGetFrameTime();
	SkillManager::GetInstance().CooldownCountFlame += AEFrameRateControllerGetFrameTime();

	if(curAttack_ == nullptr)
	{
		SkillManager::GetInstance().KeyCheck();
		SkillManager::GetInstance().SetSkillType(owner_->GetComponent<Player>()->level_);
		if (AEInputCheckCurr(AEVK_LBUTTON)
			&& meleeAttack_->GetComponent<MeleeAttack>()->GetCooldown()
			<= SkillManager::GetInstance().CooldownCountMelee
			&& SkillManager::GetInstance().type == cScorching)
		{
			curAttack_ = meleeAttack_->GetComponent<MeleeAttack>();
			curAttack_->On();
		}
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

	//switch (SkillManager::GetInstance().type)
	//{
	//case	cScorching:
	//	if (AEInputCheckCurr(AEVK_LBUTTON)
	//		&& meleeAttack_->GetComponent<MeleeAttack>()->GetCooldown()
	//		<= SkillManager::GetInstance().CooldownCountMelee
	//		&& SkillManager::GetInstance().type == Default)
	//	{
	//		curAttack_ = meleeAttack_->GetComponent<MeleeAttack>();
	//		curAttack_->On();
	//	}
	//	break;
	//case	cFlame:
	//	if (AEInputCheckCurr(AEVK_LBUTTON)
	//		&& Skills_Flame->GetComponent<Flame>()->GetCooldown()
	//		<= SkillManager::GetInstance().CooldownCountFlame
	//		&& SkillManager::GetInstance().type == Default)
	//	{
	//		curAttack_ = Skills_Flame->GetComponent<Flame>();
	//		curAttack_->On();
	//	}
	//	break;
	//case	cHaste:
	//	if (AEInputCheckCurr(AEVK_LBUTTON)
	//		&& meleeAttack_->GetComponent<MeleeAttack>()->GetCooldown()
	//		<= SkillManager::GetInstance().CooldownCountMelee
	//		&& SkillManager::GetInstance().type == Default)
	//	{

	//	}
	//	break;
	//case	cFireball:
	//	if (AEInputCheckCurr(AEVK_LBUTTON)
	//		&& meleeAttack_->GetComponent<MeleeAttack>()->GetCooldown()
	//		<= SkillManager::GetInstance().CooldownCountMelee
	//		&& SkillManager::GetInstance().type == Default)
	//	{

	//	}
	//	break;
	//case	cEating_Oxyzen:
	//	if (AEInputCheckCurr(AEVK_LBUTTON)
	//		&& meleeAttack_->GetComponent<MeleeAttack>()->GetCooldown()
	//		<= SkillManager::GetInstance().CooldownCountMelee
	//		&& SkillManager::GetInstance().type == Default)
	//	{

	//	}
	//	break;
	//case	cMeteor:
	//	if (AEInputCheckCurr(AEVK_LBUTTON)
	//		&& Skills_Meteor->GetComponent<Meteor>()->GetCooldown()
	//		<= SkillManager::GetInstance().CooldownCountMeteor
	//		&& SkillManager::GetInstance().type == Default)
	//	{
	//		curAttack_ = Skills_Meteor->GetComponent<Meteor>();
	//		curAttack_->On();
	//	}
	//	break;
	//case	cInferno:
	//	if (AEInputCheckCurr(AEVK_LBUTTON)
	//		&& meleeAttack_->GetComponent<MeleeAttack>()->GetCooldown()
	//		<= SkillManager::GetInstance().CooldownCountMelee
	//		&& SkillManager::GetInstance().type == Default)
	//	{

	//	}
	//	break;
	//default:
	//	curAttack_ = nullptr;
	//	break;
	//}

	//if (AEInputCheckCurr(AEVK_LBUTTON))
	//{
	//	if (AEInputCheckCurr(AEVK_LBUTTON)
	//		&& meleeAttack_->GetComponent<MeleeAttack>()->GetCooldown()
	//		<= SkillManager::GetInstance().CooldownCountMelee)
	//	{
	//		curAttack_ = meleeAttack_->GetComponent<MeleeAttack>();
	//		SkillManager::GetInstance().other = true;
	//		curAttack_->On();
	//	}

	//	else if (SkillManager::GetInstance().type == cMeteor
	//		&& Skills_Meteor->GetComponent<Meteor>()->GetCooldown()
	//		<= SkillManager::GetInstance().CooldownCountMeteor)
	//	{
	//		curAttack_ = Skills_Meteor->GetComponent<Meteor>();
	//		SkillManager::GetInstance().other = true;
	//		curAttack_->On();
	//	}

	//	else if (SkillManager::GetInstance().type == cFlame
	//		&& Skills_Flame->GetComponent<Flame>()->GetCooldown()
	//		<= SkillManager::GetInstance().CooldownCountFlame)
	//	{
	//		curAttack_ = Skills_Flame->GetComponent<Flame>();
	//		SkillManager::GetInstance().other = true;
	//		curAttack_->On();
	//	}

	//	else if (SkillManager::GetInstance().type == Default)
	//		SkillManager::GetInstance().resetKeys();
	//}

	text_->SetString(std::to_string(hp_) + "/" + std::to_string(exp_));
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
}

void Player::LevelUp()
{
	if (level_ >= maxLevel_)
		return;

	level_++;
	exp_ = 0;

	maxHp_ += int(maxHp_ * hpGrowthRate_ / 100);
	hp_ = maxHp_;
}

void Player::AddHp(int hp)
{
	hp_ += hp;
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
