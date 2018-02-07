#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.hpp"

#include <map>

namespace Engine { namespace Entity {

	// A very simple, kinda like holder/storage class for entity objects
	class EntityManager final
	{
		public:
			static EntityManager& getInstance()
			{
				static EntityManager theInstance{};
				return theInstance;
			}
			
			std::map<std::string, std::shared_ptr<Entity>> GetEnts()
			{
				return m_entities;
			}

			std::shared_ptr<Entity> Find(const std::string& t_name)
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

			void Store(const std::string& t_name, std::shared_ptr<Entity> t_entity)
			{
				if (m_entities.find(t_name) == m_entities.end())
					m_entities[t_name] = t_entity;
			}

			void Update(float t_deltaTime)
			{
				for (auto ent : m_entities)
					ent.second->Update(t_deltaTime);
			}

		private:
			std::map<std::string, std::shared_ptr<Entity>> m_entities;
	};

} }

#endif // !ENTITY_MANAGER_H