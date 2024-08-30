#include "Audio.h"

#include "../Manager/ResourceManager.h"
#include "../Resource/AudioResource.h"
#include "../GameObject/GameObject.h"

Audio::Audio(GameObject* owner) : AudioComponent(owner), group_(), audio_(), audioName_()
{
	group_ = AEAudioCreateGroup();
}

Audio::~Audio()
{
	ResourceManager::GetInstance().Unload(audioName_);
	AEAudioUnloadAudioGroup(group_);
}

void Audio::RemoveFromManager()
{
	ComponentManager<AudioComponent>::GetInstance().DeleteComponent(static_cast<AudioComponent*>(this));
}

void Audio::Update()
{
	if (!playing_)
	{
		playing_ = true;
		AEAudioPlay(audio_, group_, volume_, pitch_, -1);
	}
}

void Audio::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");
	if (compData != data.end())
	{
		auto it = compData->find("audioName");
		audioName_ = it.value();
		SetAudio(audioName_);

		it = compData->find("volume");
		volume_ = it.value();

		it = compData->find("pitch");
		pitch_ = it.value();

		it = compData->find("loop");
		loop_ = it.value();

		it = compData->find("playing");
		playing_ = it.value();
	}
}

json Audio::SaveToJson()
{
	json data, compData;
	data["type"] = TypeName;

	compData["audioName"] = audioName_;
	compData["volume"] = volume_;
	compData["pitch"] = pitch_;
	compData["loop"] = loop_;
	compData["playing"] = playing_;

	data["compData"] = compData;
	return data;
}

void Audio::SetAudio(std::string name)
{
	audioName_ = name;
	audio_ = *(ResourceManager::GetInstance().Get<AudioResource>(name)->GetData());
}

ComponentSerializer* Audio::CreateComponent(GameObject* owner)
{
	if (!owner->AddComponent<Audio>())
		std::cout << "Audio::CreateComponent() Component already exists" << std::endl;

	return owner->GetComponent<Audio>();
}

