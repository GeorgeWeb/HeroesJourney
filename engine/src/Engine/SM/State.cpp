#include "State.hpp"

namespace Engine { namespace SM {

	void State::Pause()
	{
		for (auto& ent : m_entities)
		{
			ent.second->SetVisible(false);
			ent.second->SetAlive(false);
		}
	}

	void State::Resume()
	{
		for (auto& ent : m_entities)
		{
			if (ent.second->showOnCreate)
			{
				ent.second->SetVisible(true);
				ent.second->SetAlive(true);
			}
			else
			{
				ent.second->SetVisible(false);
				ent.second->SetAlive(false);
			}
		}
	}

	void State::AddEntity(const std::string& t_name, std::shared_ptr<ECM::Entity> t_entity)
	{
		if (m_entities.find(t_name) == m_entities.end())
		{
			if (t_entity == nullptr)
				throw("The entity you are trying to access is not initialised! ");
			else
				m_entities[t_name] = t_entity;
		}
	}

} }