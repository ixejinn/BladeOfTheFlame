#include "ResourceManager.h"
#include "../Resource/TextureResource.h"

template<typename T>
inline T* ResourceManager::Get(const std::string& name)
{
	Extension ext = StringToExtension(name);

	if (resources_[ext].find(name) == resources_[ext].end())
	{
		std::unique_ptr<T> ptr(new T());
		resources_[ext].insert({ name, std::move(ptr) });
		resources_[ext][name]->Load(name);
	}

	resources_[ext][name]->counter_++;

	return static_cast<T*>(resources_[ext][name].get());
}