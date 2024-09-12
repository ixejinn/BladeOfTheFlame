#include "FontResource.h"

#include <iostream>
#include "Resource.h"

FontResource::~FontResource()
{
	Unload();
	delete id;
}

void FontResource::Load(const std::string& name)
{
	id = new s8(AEGfxCreateFont(name.c_str(), 20));
	data_ = static_cast<void*>(id);
}

void FontResource::Unload()
{
	if (data_ != nullptr)
		AEGfxDestroyFont(GetData());
}

s8 FontResource::GetData() const
{
	return *(static_cast<s8*>(data_));
}
