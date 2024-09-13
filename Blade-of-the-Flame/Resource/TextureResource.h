#pragma once
#include <string>
#include "Resource.h"
#include "AEEngine.h"

class TextureResource : public Resource
{
private:
	std::string name_;

	TextureResource();

public:
	~TextureResource() { Unload(); }

	void Load(const std::string& name) override;
	void Unload() override;

	const std::string& GetName() { return name_; }
	AEGfxTexture* GetData() const;

	friend class ResourceManager;
};