#include "AnimationComp.h"
#include "../Manager/GameObjectManager.h"
#include "Sprite.h"
#include <algorithm>

AnimationComp::AnimationComp(GameObject* owner) : GraphicsComponent(owner)
{
	owner_->AddComponent<Sprite>();

	//AddAnimation("Idle");
	//AddAnimation("walk");
	//AddAnimation("Attack");
	//AddAnimation("Hit");
	//AddAnimation("Dead");

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
	double dt = AEFrameRateControllerGetFrameRate();

	owner_->GetComponent<Sprite>()->SetTexture(anime[currentAnime]->GetDetail());

	elapsedTime += dt;

	if (elapsedTime >= animationTerm)
	{
		elapsedTime = 0;
		anime[currentAnime]->p++;
	}
}

void AnimationComp::RemoveFromManager()
{
	ComponentManager<GraphicsComponent>::GetInstance().DeleteComponent(static_cast<GraphicsComponent*>(this));
}

void AnimationComp::AddAnimation(std::string other)//�ִϸ��̼� Ÿ�Լ���
{
	Animation* p = new Animation;
	if (anime.find(other) == anime.end())
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
	if (anime[currentAnime]->animationplay != false)
	{
		return true;
	}
	else
		return false;
}

void AnimationComp::AnimationLoop(int init, int max, std::string name, std::string type)
{
	AddAnimation(type);
	for (int i = init; i < max; i++)
	{
		std::string anim = name + std::to_string(i) + ".png";
		AddDetail(anim, type);
	}
	for (int i = max-1; i >= init; i--)
	{
		std::string anim = name + std::to_string(i) + ".png";
		AddDetail(anim, type);
	}
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
	if (anime.find(which) == anime.end())
		AddAnimation(which);

	anime[which]->detail.push_back(s);
}

void AnimationComp::DeleteDetail(std::string s, std::string which)
{
	auto newEnd = std::remove(anime[which]->detail.begin(), anime[which]->detail.end(), s);
	anime[which]->detail.erase(newEnd, anime[which]->detail.end());
}
