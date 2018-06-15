#include "ResourceManager.h"

namespace engine {

	ResourceManager::ResourceManager(){


	}


	ResourceManager::~ResourceManager(){


	}

	void ResourceManager::AddResource(std::string key, Resource* r) {

		m_resources[key] = r;
	}

	Resource* ResourceManager::GetResource(std::string key) {

		auto it =  m_resources.find(key);
		if (it != m_resources.end()) {

			return m_resources[key];
		}
		return nullptr;
	}
}