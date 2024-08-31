#include "AnimationComp.h"
#include "../Manager/GameObjectManager.h"
#include "Sprite.h"
#include <algorithm>

AnimationComp::AnimationComp(GameObject* owner) : GraphicsComponent(owner)
{
	AddAnimation("Idle");
	AddAnimation("walk");
	AddAnimation("Attack");
	AddAnimation("Hit");
	AddAnimation("Dead");
	currentAnime = "Idle";
}

AnimationComp::~AnimationComp()
{
	for (auto& it : anime)
	{
		delete it.second;
	}
	anime.clear();
}

void AnimationComp::Update()
{
	float dt = AEFrameRateControllerGetFrameRate();
	auto it = anime.find(currentAnime);
	owner_->GetComponent<Sprite>()->SetTexture(it->second->GetDetail());
	elapsedTime += dt;
	if (elapsedTime >= animationTerm)
	{
		elapsedTime = 0;
		anime.find(currentAnime)->second->p++;
	}
}

void AnimationComp::AddAnimation(std::string other)
{
	Animation* p = new Animation;
	anime.emplace(other, p);
}

void AnimationComp::DeleteAnimation(std::string other)
{
	auto it = anime.find(other);
	if (it != anime.end()) {
		delete it->second;
		anime.erase(it);
	}
}

bool AnimationComp::CurrentAnimationOver()
{
	if (anime.find(currentAnime)->second->animationplay != false)
	{
		return true;
	}
	else
		return false;
}


ComponentSerializer* AnimationComp::CreateAnimationComp(GameObject* owner)
{
	if (!owner->AddComponent<AnimationComp>())
		std::cout << "AnimationComp::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<AnimationComp>();
}

Animation::Animation()
{
	detail.clear();
	animationplay = false;
}

Animation::~Animation()
{
	detail.clear();
}

std::string Animation::GetDetail()
{
	animationplay = false;
	if (detail.size() < p + 1)
	{
		p = 0;
		animationplay = true;
	}
	return detail[p];
}

void AnimationComp::AddDetail(std::string s, std::string which)
{
	anime.find(which)->second->detail.push_back(s);
}

void AnimationComp::DeleteDetail(std::string s, std::string which)
{
	auto newEnd = std::remove(anime.find(which)->second->detail.begin(), anime.find(which)->second->detail.end(), s);
	anime.find(which)->second->detail.erase(newEnd, anime.find(which)->second->detail.end());
}
