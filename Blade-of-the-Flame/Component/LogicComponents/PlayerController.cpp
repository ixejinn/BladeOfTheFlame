#include "PlayerController.h"

#include "../../GameObject/GameObject.h"

PlayerController::PlayerController(GameObject* owner) : LogicComponent(owner) {}

void PlayerController::Update()
{
	Transform* trans = owner_->GetComponent<Transform>();
	RigidBody* rb = owner_->GetComponent<RigidBody>();

	AEVec2 moveVec{ 0.f, 0.f };

	if (!onlyUpDown)
	{
		if (AEInputCheckCurr(moveKeys_[LEFT]))
			moveVec.x--;

		if (AEInputCheckCurr(moveKeys_[RIGHT]))
			moveVec.x++;
	}

	if (AEInputCheckCurr(moveKeys_[UP]))
		moveVec.y++;

	if (AEInputCheckCurr(moveKeys_[DOWN]))
		moveVec.y--;

	float squareLen = AEVec2SquareLength(&moveVec);
	if (squareLen >= 1.2f)
	{
		AEVec2 moveVecCopy = moveVec;
		AEVec2Normalize(&moveVec, &moveVecCopy);
	}
	rb->AddVelocity(moveVec * moveSpeed_);

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

ComponentSerializer* PlayerController::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<PlayerController>())
		std::cout << "PlayerController::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<PlayerController>();
}
