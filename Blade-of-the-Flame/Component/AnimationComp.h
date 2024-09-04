#pragma once
#include "GraphicsComponent.h"
#include "AEEngine.h"
#include <vector>
#include <map>
#include <string>

class Animation
{
public:
	Animation();
	~Animation();
	int currentFrame = 0;
	int p = 0;

	std::vector<std::string> detail;

	std::string GetDetail();
	bool animationplay;

};

class AnimationComp : public GraphicsComponent
{
private:
	std::string currentAnime;
	std::map<std::string, Animation*> anime;
	float animationTerm = 1000;
	float elapsedTime = 0;
public:
	AnimationComp(GameObject* owner);
	~AnimationComp();
	void Update() override;

	void AddAnimation(std::string);
	void DeleteAnimation(std::string);
	bool CurrentAnimationOver();
	void AddDetail(std::string s, std::string which);
	void DeleteDetail(std::string s, std::string which);

	void SetTerm(float other) { animationTerm = other; }
	void ChangeAnimation(std::string s) {	currentAnime = s;	};

	void RemoveFromManager() override;

	static constexpr const char* AnimationTypeName = "AnimationTypeName";
	static ComponentSerializer* CreateAnimationComp(GameObject* owner);

	void LoadFromJson(const json&) override {};
	json SaveToJson() override { return NULL; }
};