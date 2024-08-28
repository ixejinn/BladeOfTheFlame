#include "Player.h"

#include <typeindex>
#include <chrono>
#include "AEGraphics.h"
#include "../../GameObject/GameObject.h"
#include "../../Event/Event.h"
#include "../../Manager/EventManager.h"
#include "../../Utils/Utils.h"

Player::Player(GameObject* owner) : LogicComponent(owner)
{
	//// TODO: GameObject에 Component 담는 순서 주의, Serializer 부분 수정 필요
	PlayerController* pc = owner_->GetComponent<PlayerController>();
	if (!pc)
		std::cerr << "Player::Player() PlayerController not found" << std::endl;

	pc->MultiplyMoveSpeed(moveSpeed_);
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
		GameOverEvent* event{ new GameOverEvent() };
		event->from_ = owner_;
		EventManager::GetInstance().AddEvent(event);
	}

	/* SET CAMERA */
	Transform* trans = owner_->GetComponent<Transform>();
	AEVec2 pos = trans->GetPosition();
	AEGfxSetCamPosition(pos.x, pos.y);

	//f32 x_, y_;
	//AEGfxGetCamPosition(&x_, &y_);
	//std::cout << x_ << ", " << y_ << std::endl;

	/* ATTACK */
	static std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
	AEInputInit();
	if (AEInputCheckCurr(AEVK_LBUTTON))
	{
		s32 x, y;
		AEInputGetCursorPosition(&x, &y);
		//std::cout << x << ", " << y << std::endl;
		BasicAttack(x, y);
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

	// Collision event
	if (eventType == std::type_index(typeid(CollisionEvent)))
	{
		//// TODO: 해당 부분 Collision system 수정 필요
		if (dynamic_cast<CollisionEvent*>(event)->to_ != owner_)
			return;


	}
}

void Player::LevelUp()
{
	if (level_ >= maxLevel_)
		return;

	level_++;
	exp_ = 0;

	maxHp_ += int(maxHp_ * hpGrowthRate_ / 100);
	hp_ = maxHp_;

	baseDmg_ += int(baseDmg_ * baseDmgGrowthRate_ / 100);
	
	if (level_ == 3)
		attackRange_ = 7;
}

void Player::BasicAttack(s32 x, s32 y)
{
	AEVec2 attackDir{ x - windowWidth / 2, y - windowHeight / 2 }, unitDir;
	AEVec2Normalize(&unitDir, &attackDir);

	attackDir = unitDir * attackRange_ * 10.f;
}

ComponentSerializer* Player::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Player>())
		std::cout << "Transform::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Player>();
}
