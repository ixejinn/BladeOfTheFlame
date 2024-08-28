#include "AudioResource.h"

void AudioResource::Load(const std::string& name)
{
	AEAudio data = AEAudioLoadMusic(name.c_str());
	data_ = static_cast<void*>(&data);
}

void AudioResource::Unload()
{
	AEAudioUnloadAudio(*(static_cast<AEAudio*>(data_)));
}

AEAudio* AudioResource::GetData() const
{
	return static_cast<AEAudio*>(data_);
}
