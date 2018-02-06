#include "EntityManager.hpp"

namespace Engine { namespace Entity {

	EntityManager& EntityManager::getInstance()
	{
		static EntityManager theInstance{};
		return theInstance;
	}

	inline std::shared_ptr<Entity> EntityManager::Find(const std::string& t_name)
	{
		return m_entities[t_name];
	}

	inline void EntityManager::Store(const std::string& t_name, std::shared_ptr<Entity> t_entity)
	{
		m_entities[t_name] = t_entity;
	}

} }