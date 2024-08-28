#pragma once
#include <string>
#include "AudioComponent.h"
#include "../Manager/ComponentManager.h"
#include "AEAudio.h"

class Audio : public AudioComponent
{
private:
	AEAudioGroup group_;

	AEAudio audio_;
	std::string audioName_;

	float volume_ = 0.5f;
	float pitch_ = 1;

	bool loop_ = true;
	bool playing_ = false;

	Audio(GameObject* owner);
	~Audio();

public:
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void SetAudio(std::string name);

	// for StateSerializer
	static constexpr const char* TypeName = "Audio";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<AudioComponent>;
};