#pragma once
#include <string>
#include "Resource.h"
#include "AEAudio.h"

class AudioResource : public Resource
{
private:
	AudioResource() = default;
	AEAudio data;
public:
	~AudioResource() { Unload(); }

	void Load(const std::string& name) override;
	void Unload() override;

	AEAudio* GetData() const;

	friend class ResourceManager;
};