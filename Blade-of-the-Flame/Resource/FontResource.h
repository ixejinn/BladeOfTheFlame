#pragma once
#include <string>
#include "Resource.h"
#include "AEEngine.h"

class FontResource : public Resource
{
private:
	FontResource() = default;

public:
	~FontResource() { Unload(); }

	void Load(const std::string& name) override;
	void Unload() override;

	s8 GetData() const;

	friend class ResourceManager;
};