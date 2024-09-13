#include "AnimationComp.h"

#include <algorithm>
#include "Sprite.h"
#include "../Manager/GameObjectManager.h"
#include "../Manager/ResourceManager.h"


AnimationComp::AnimationComp(GameObject* owner) : GraphicsComponent(owner)
{
	owner_->AddComponent<Sprite>();

	//AddAnimation("Idle");
	//AddAnimation("walk");
	//AddAnimation("Attack");
	//AddAnimation("Hit");
	//AddAnimation("Dead");

	currentAnime = "Idle";

	sp_ = owner_->GetComponent<Sprite>();
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

	sp_->SetTexture(anime[currentAnime]->GetDetail());

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

void AnimationComp::AddAnimation(std::string type)//�ִϸ��̼� Ÿ�Լ���
{
	if (anime.find(type) == anime.end())
		anime.emplace(type, new Animation());
}

void AnimationComp::DeleteAnimation(std::string type)
{
	auto it = anime.find(type);
	if (it != anime.end()) {
		delete it->second;
		anime.erase(it);
	}
}

bool AnimationComp::CurrentAnimationOver()
{
	if (anime[currentAnime]->animationPlay != false)
		return true;
	else
		return false;
}

void AnimationComp::AnimationLoop(int init, int max, std::string name, std::string type)
{
	AddAnimation(type);
	anime[type]->detail.reserve(2 * (max - init) - 1);

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

Animation::Animation() : currentFrame(0), p(0), animationPlay(false)
{
	//detail.clear();
	currentFrame = 0;
	p = 0;
	animationPlay = false;
}

Animation::~Animation()
{
	//detail.clear();
}

TextureResource* Animation::GetDetail()
{
	animationPlay = false;
	if (p >= detail.size())
	{
		p = 0;
		animationPlay = true;
	}
	return detail[p];
}

void AnimationComp::AddDetail(std::string name, std::string which)
{
	if (anime.find(which) == anime.end())
		AddAnimation(which);

	anime[which]->detail.push_back(ResourceManager::GetInstance().Get<TextureResource>(name));
}

void AnimationComp::DeleteDetail(std::string name, std::string which)
{
	//auto newEnd = std::remove(anime[which]->detail.begin(), anime[which]->detail.end(), name);
	//anime[which]->detail.erase(newEnd, anime[which]->detail.end());
}
