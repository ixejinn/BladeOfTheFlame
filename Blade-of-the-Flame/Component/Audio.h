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
	bool playing_ = true;

	Audio(GameObject* owner);
	~Audio();

public:
	void RemoveFromManager() override;

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	void SetAudio(const std::string& name);
	void SetLoop(bool b) { loop_ = b; }
	void SetPlaying(bool b) { playing_ = b; }

	// for StateSerializer
	static constexpr const char* TypeName = "Audio";
	static ComponentSerializer* CreateComponent(GameObject* owner);

	friend class ComponentManager<AudioComponent>;
};