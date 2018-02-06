#include "State.hpp"

namespace Engine { namespace SM {

	void State::AddEntity(const std::string& t_name, std::shared_ptr<Entity::Entity> t_entity)
	{
		if (t_entity == nullptr)
			throw("This entity is not initialised! ");

		m_entities[t_name] = t_entity;
	}

} }