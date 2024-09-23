#include "PlayerController.h"

#include "../../GameObject/GameObject.h"

PlayerController::PlayerController(GameObject* owner) : LogicComponent(owner) {}

void PlayerController::RemoveFromManager()
{
	ComponentManager<LogicComponent>::GetInstance().DeleteComponent(static_cast<LogicComponent*>(this));
}

void PlayerController::Update()
{
	Transform* trans = owner_->GetComponent<Transform>();
	RigidBody* rb = owner_->GetComponent<RigidBody>();

	AEVec2 moveVec{ 0.f, 0.f };
	float speed = moveSpeed_;

	Direction curDir = STOP;
	moveState_ = false;

	if (!onlyUpDown)
	{
		if (AEInputCheckCurr(moveKeys_[LEFT]))
		{
			moveVec.x--;
			curDir = LEFT;
		}

		if (AEInputCheckCurr(moveKeys_[RIGHT]))
		{
			moveVec.x++;
			curDir = RIGHT;
		}
	}

	if (curDir != STOP)
	{
		lastMoveDirection_ = curDir;
		moveState_ = true;
	}

	if (AEInputCheckCurr(moveKeys_[UP]))
	{
		moveVec.y++;
		moveState_ = true;
	}

	if (AEInputCheckCurr(moveKeys_[DOWN]))
	{
		moveVec.y--;
		moveState_ = true;
	}

	dashState_ = false;
	if (dashKey_ != 0x00)
	{
		std::chrono::duration<double> dt = std::chrono::system_clock::now() - timeStart_;

		if (dt.count() >= dashCooldown_ && AEInputCheckCurr(dashKey_))
		{
			dashState_ = true;
			timeStart_ = std::chrono::system_clock::now();

			speed *= 30.0;
		}
	}		

	float squareLen = AEVec2SquareLength(&moveVec);
	if (squareLen >= 1.2f)
	{
		AEVec2 moveVecCopy = moveVec;
		AEVec2Normalize(&moveVec, &moveVecCopy);
	}
	rb->AddVelocity(moveVec * speed);

	if (rotKeys_[LEFT] != 0x00 && AEInputCheckCurr(rotKeys_[LEFT]))
		trans->SetRotation(trans->GetRotation() + rotSpeed_);

	if (rotKeys_[RIGHT] != 0x00 && AEInputCheckCurr(rotKeys_[RIGHT]))
		trans->SetRotation(trans->GetRotation() - rotSpeed_);

	if (stopKey_ != 0x00 && AEInputCheckCurr(stopKey_))
		rb->ClearVelocity();
}

void PlayerController::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("moveKeys");
		for (int i = 0; i < 4; i++)
			moveKeys_[i] = (it->begin() + i).value();

		it = compData->find("rotKeys");
		for (int i = 0; i < 2; i++)
			rotKeys_[i] = (it->begin() + i).value();

		it = compData->find("stop");
		stopKey_ = it->begin().value();

		it = compData->find("moveSpeed");
		moveSpeed_ = it->begin().value();

		it = compData->find("rotSpeed");
		rotSpeed_ = it->begin().value();
	}
}

json PlayerController::SaveToJson()
{
	json data, compData;
	data["type"] = TypeName;

	compData["moveKeys"] = { moveKeys_[LEFT], moveKeys_[RIGHT], moveKeys_[UP], moveKeys_[DOWN] };
	compData["rotKeys"] = { rotKeys_[LEFT], rotKeys_[RIGHT] };
	compData["stop"] = stopKey_;
	compData["moveSpeed"] = moveSpeed_;
	compData["rotSpeed"] = rotSpeed_;

	data["compData"] = compData;
	return data;
}

void PlayerController::SetDashKey(uint8_t key)
{
	dashKey_ = key;

	timeStart_ = std::chrono::system_clock::now();
}

ComponentSerializer* PlayerController::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<PlayerController>())
		std::cout << "PlayerController::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<PlayerController>();
}
