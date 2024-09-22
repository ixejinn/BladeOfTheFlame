#include "EnvironmentManager.h"

#include "AEVec2.h"
#include "GameObjectManager.h"
#include "../Utils/Utils.h"

GameObjectManager& objMgr = GameObjectManager::GetInstance();

EnvironmentManager::EnvironmentManager()
{
	Transform* trans = nullptr;

	//zoom_ = 1.f;

	for (int i = 0; i < 3; i++)
	{
		float xPos = -zoom_ * windowWidth + zoom_ * windowWidth * i;

		GameObject* up = objMgr.CreateObject("_UP" + std::to_string(i));
		up->AddComponent<Transform>();
		trans = up->GetComponent<Transform>();
		trans->SetScale({ windowWidth * zoom_, windowHeight * zoom_ });
		trans->SetPosition(xPos, zoom_ * windowHeight);
		up->AddComponent<Sprite>();
		up->GetComponent<Sprite>()->SetTexture(textureName);
		up_.emplace_back(trans);

		GameObject* center = objMgr.CreateObject("_CENTER" + std::to_string(i));
		center->AddComponent<Transform>();
		trans = center->GetComponent<Transform>();
		trans->SetScale({ windowWidth * zoom_, windowHeight * zoom_ });
		trans->SetPosition(xPos, 0);
		center->AddComponent<Sprite>();
		center->GetComponent<Sprite>()->SetTexture(textureName);
		center_.emplace_back(trans);

		GameObject* down = objMgr.CreateObject("_DOWN" + std::to_string(i));
		down->AddComponent<Transform>();
		trans = down->GetComponent<Transform>();
		trans->SetScale({ windowWidth * zoom_, windowHeight * zoom_ });
		trans->SetPosition(xPos, -zoom_ * windowHeight);
		down->AddComponent<Sprite>();
		down->GetComponent<Sprite>()->SetTexture(textureName);
		down_.emplace_back(trans);
	}

	bgm_ = objMgr.CreateObject("_BGM");
	bgm_->AddComponent<Audio>();
	//bgm_->GetComponent<Audio>()->SetAudio("Assets/bouken.mp3");
}

void EnvironmentManager::SetPlayerTransform()
{
	playerTrans_ = objMgr.GetObjectA("player")->GetComponent<Transform>();
}

void EnvironmentManager::Update()
{
	if (!playerTrans_)
	{
		playerTrans_ = objMgr.GetObjectA("player")->GetComponent<Transform>();
		if (!playerTrans_)
			return;
	}
	AEVec2 playerPos = playerTrans_->GetPosition();

	AEVec2 betweenPos = center_[1]->GetPosition();
	AEVec2 newBetweenPos;

	/* CHECK X COORD */
	// player가 center[0]에 위치
	//std::cout << playerPos.x << "    " << betweenPos.x - zoom_ / 2.f * windowWidth << std::endl;
	if (playerPos.x < betweenPos.x - zoom_ / 2.f * windowWidth)
	{
		Transform* tmp = nullptr;
		newBetweenPos = center_.front()->GetPosition();
		newBetweenPos.x -= zoom_ * windowWidth;

		tmp = center_.back();
		tmp->SetPosition(newBetweenPos);
		center_.pop_back();
		center_.push_front(tmp);

		tmp = up_.back();
		tmp->SetPosition(newBetweenPos.x, newBetweenPos.y + zoom_ * windowHeight);
		up_.pop_back();
		up_.push_front(tmp);

		tmp = down_.back();
		tmp->SetPosition(newBetweenPos.x, newBetweenPos.y - zoom_ * windowHeight);
		down_.pop_back();
		down_.push_front(tmp);
	}
	// player가 center[2]에 위치
	else if (playerPos.x > betweenPos.x + zoom_ / 2.f * windowWidth)
	{
		Transform* tmp = nullptr;
		newBetweenPos = center_.back()->GetPosition();
		newBetweenPos.x += zoom_ * windowWidth;

		tmp = center_.front();
		tmp->SetPosition(newBetweenPos);
		center_.pop_front();
		center_.push_back(tmp);

		tmp = up_.front();
		tmp->SetPosition(newBetweenPos.x, newBetweenPos.y + zoom_ * windowHeight);
		up_.pop_front();
		up_.push_back(tmp);

		tmp = down_.front();
		tmp->SetPosition(newBetweenPos.x, newBetweenPos.y - zoom_ * windowHeight);
		down_.pop_front();
		down_.push_back(tmp);
	}

	/* CHECK Y COORD */
	// player가 up[1]에 위치
	if (playerPos.y > betweenPos.y + zoom_ / 2.f * windowHeight)
	{
		newBetweenPos = up_[1]->GetPosition();

		for (int i = 0; i < 3; i++)
		{
			center_.push_back(up_[i]);
			down_.push_back(center_[i]);
			up_.push_back(down_[i]);
		}

		for (int i = 0; i < 3; i++)
		{
			center_.pop_front();
			down_.pop_front();
			up_.pop_front();
		}

		newBetweenPos.y += zoom_ * windowHeight;
		for (int i = 0; i < 3; i++)
			up_[i]->SetPosition(newBetweenPos.x - zoom_ * windowWidth + zoom_ * i * windowWidth, newBetweenPos.y);
	}
	// player가 down[1]에 위치
	else if (playerPos.y < betweenPos.y - zoom_ / 2.f * windowHeight)
	{
		newBetweenPos = down_[1]->GetPosition();

		for (int i = 0; i < 3; i++)
		{
			center_.push_back(down_[i]);
			up_.push_back(center_[i]);
			down_.push_back(up_[i]);
		}

		for (int i = 0; i < 3; i++)
		{
			center_.pop_front();
			up_.pop_front();
			down_.pop_front();
		}

		newBetweenPos.y -= zoom_ * windowHeight;
		for (int i = 0; i < 3; i++)
			down_[i]->SetPosition(newBetweenPos.x - zoom_ * windowWidth + zoom_ * i * windowWidth, newBetweenPos.y);
	}

}
