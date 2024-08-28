#include "ResourceManager.h"

#include <stdexcept>

ResourceManager::Extension ResourceManager::StringToExtension(const std::string& fileName)
{
	std::string extStr = fileName.substr(fileName.find_last_of('.') + 1);

	if (stringToExtension_.find(extStr) == stringToExtension_.end())
		throw std::invalid_argument("[ERROR] ResourceManager StringToExtension | Invalid file name " + fileName);
	return stringToExtension_[extStr];
}

void ResourceManager::Unload(const std::string& fileName)
{
	Extension ext = StringToExtension(fileName);

	if (resources_[ext].find(fileName) == resources_[ext].end())
		throw std::invalid_argument("[ERROR] ResourceManager Unload | Invalid resource " + fileName);

	resources_[ext][fileName]->counter_--;
	if (resources_[ext][fileName]->counter_ == 0 && !resources_[ext][fileName]->persistent_)
		resources_[ext][fileName]->Unload();
}

void ResourceManager::UnloadAll(bool persistent)
{
	for (auto extIt = resources_.begin(); extIt != resources_.end(); )
	{
		for (auto it = extIt->second.begin(); it != extIt->second.end(); )
		{
			if (persistent || !it->second->persistent_)
				extIt->second.erase(it++);
			else
				it++;
		}
	}
}