#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.hpp"

#include <map>

namespace Engine { namespace Entity {

	// A very simple, kinda like holder/storage class for entity objects
	class EntityManager final
	{
		public:
			static EntityManager& getInstance();
			
			inline std::shared_ptr<Entity> Find(const std::string& t_name);
			inline void Store(const std::string& t_name, std::shared_ptr<Entity> t_entity);

		private:
			std::map<std::string, std::shared_ptr<Entity>> m_entities;
	};

} }

#endif // !ENTITY_MANAGER_H