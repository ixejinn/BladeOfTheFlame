#include "TextureResource.h"

TextureResource::TextureResource() : name_() {}

void TextureResource::Load(const std::string& name)
{
	name_ = name;
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
