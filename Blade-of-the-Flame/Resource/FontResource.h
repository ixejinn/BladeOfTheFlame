#pragma once
#include <string>
#include "Resource.h"
#include "AEEngine.h"

class FontResource : public Resource
{
private:
	s8* id = nullptr;
	FontResource() = default;

public:
	~FontResource();

	void Load(const std::string& name) override;
	void Unload() override;

	s8 GetData() const;

	friend class ResourceManager;
};