#include "EntityManager.hpp"

namespace Engine { namespace Entity {

	EntityManager& EntityManager::getInstance()
	{
		static EntityManager theInstance{};
		return theInstance;
	}

	inline std::shared_ptr<Entity> EntityManager::Find(const std::string& t_name)
	{
		if (m_entities.find(t_name) == m_entities.end())
		{
			throw("The entity you are trying to access does not exist! ");
		}
		else
		{
			if (m_entities[t_name] == nullptr)
				throw("The entity you are trying to access is not initialised! ");
			else
				return m_entities[t_name];
		}
	}

	inline void EntityManager::Store(const std::string& t_name, std::shared_ptr<Entity> t_entity)
	{
		if (m_entities.find(t_name) != m_entities.end())
			m_entities[t_name] = t_entity;
	}

} }