#pragma once
#include <string>
#include "Resource.h"
#include "AEEngine.h"

class TextureResource : public Resource
{
private:
	TextureResource() = default;

public:
	~TextureResource() { Unload(); }

	void Load(const std::string& name) override;
	void Unload() override;

	AEGfxTexture* GetData() const;

	friend class ResourceManager;
};