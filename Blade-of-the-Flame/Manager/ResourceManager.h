#pragma once
#include <map>
#include <string>
#include <memory>
#include "../Resource/Resource.h"

class ResourceManager
{
	enum Extension
	{
		PNG,
		MP3,
		TTF
	};
	std::map<std::string, Extension> stringToExtension_ =
	{
		{ "png", PNG },
		{ "mp3", MP3 },
		{ "ttf", TTF }
	};

	std::map<Extension, std::map<std::string, std::unique_ptr<Resource>>> resources_;

	ResourceManager() = default;
	~ResourceManager()
	{
		UnloadAll(true);
	};

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator =(const ResourceManager&) = delete;

	Extension StringToExtension(const std::string& name);

public:
	static ResourceManager& GetInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	// @tparam T	Texture, Audio, ...
	template <typename T>
	T* Get(const std::string& name);

	void Unload(const std::string& name);

	// @param persistent	If true, unload all resources.
	//						If false, unload only resources that are not marked as persistent.
	void UnloadAll(bool persistent);
};

#include "ResourceManager.inl"