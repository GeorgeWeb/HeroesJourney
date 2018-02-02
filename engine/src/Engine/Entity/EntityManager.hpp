#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.hpp"

#include <map>

namespace Engine { namespace Entity {
	
	using EntityRef = std::shared_ptr<Entity>;

	// A very simple, kinda like holder/storage class for entity objects
	class EntityManager final
	{
		public:
			static EntityManager& getInstance()
			{
				static EntityManager theInstance{};
				return theInstance;
			}
			
			inline EntityRef Find(const std::string& t_name) { return m_entities[t_name]; }
			inline void Store(const std::string& t_name, EntityRef t_entity) { m_entities[t_name] = t_entity; }

		private:
			std::map<std::string, EntityRef> m_entities;
	};

} }

#endif // !ENTITY_MANAGER_H