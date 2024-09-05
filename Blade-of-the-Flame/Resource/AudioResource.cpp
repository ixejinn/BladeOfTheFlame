#include "AudioResource.h"

void AudioResource::Load(const std::string& name)
{
	data = AEAudioLoadMusic(name.c_str());
	data_ = static_cast<void*>(&data);
}

void AudioResource::Unload()
{
	if (data_ != nullptr)
		AEAudioUnloadAudio(*(static_cast<AEAudio*>(data_)));
	data_ = nullptr;
}

AEAudio* AudioResource::GetData() const
{
	return static_cast<AEAudio*>(data_);
}
