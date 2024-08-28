#include "TextureResource.h"

void TextureResource::Load(const std::string& name)
{
	data_ = static_cast<void*>(AEGfxTextureLoad(name.c_str()));
}

void TextureResource::Unload()
{
	if (data_ != nullptr)
		AEGfxTextureUnload(static_cast<AEGfxTexture*>(data_));
}

AEGfxTexture* TextureResource::GetData() const
{
	return static_cast<AEGfxTexture*>(data_);
}
