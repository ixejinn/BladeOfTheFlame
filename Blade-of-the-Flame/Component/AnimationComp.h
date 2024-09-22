#pragma once
#include <vector>
#include <map>
#include <string>
#include "AEEngine.h"
#include "GraphicsComponent.h"
#include "../Manager/ComponentManager.h"

class TextureResource;

struct Animation
{
	std::vector<TextureResource*> detail;

	int currentFrame;
	int p;
	bool animationPlay;

	Animation();
	~Animation();

	TextureResource* GetDetail();
};

class AnimationComp : public GraphicsComponent
{
public:
	enum Type
	{
		CUSTOM,
		APPEAR,
		DISAPPEAR
	};

private:
	Type type_ = CUSTOM;

	std::string currentAnime;
	std::map<std::string, Animation*> anime;
	float animationTerm = 1000;
	double elapsedTime = 0.0;

	Sprite* sp_ = nullptr;

	AnimationComp(GameObject* owner);
	~AnimationComp();

public:
	void Update() override;
	void RemoveFromManager() override;

	void AddAnimation(std::string type);

	void DeleteAnimation(std::string type);

	bool CurrentAnimationOver();

	void AddDetail(std::string name, std::string which);
	void DeleteDetail(std::string name, std::string which);

	void SetType(Type type);
	void SetTerm(float other) { animationTerm = other; }
	void ChangeAnimation(std::string type) { currentAnime = type; };

	Type GetType() const { return type_; }

	void AnimationLoop(int init, int max, std::string name, std::string type);

	static constexpr const char* AnimationTypeName = "AnimationTypeName";
	static ComponentSerializer* CreateAnimationComp(GameObject* owner);

	void LoadFromJson(const json&) override {};
	json SaveToJson() override { return NULL; }

	friend class ComponentManager<GraphicsComponent>;
};