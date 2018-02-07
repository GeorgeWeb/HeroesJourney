#include "State.hpp"
#include "../Entity/EntityManager.hpp"

namespace Engine { namespace SM {

	void State::Pause()
	{

	}

	void State::Resume()
	{

	}

	void State::AddEntity(const std::string& t_name, std::shared_ptr<Entity::Entity> t_entity)
	{
		Entity::EntityManager::getInstance().Store(t_name, t_entity);
	}

	std::shared_ptr<Entity::Entity> State::GetEntity(const std::string& t_name)
	{
		return Entity::EntityManager::getInstance().Find(t_name);
	}

} }