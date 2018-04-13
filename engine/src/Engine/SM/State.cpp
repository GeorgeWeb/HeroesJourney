#include "State.hpp"
#include "../Engine.hpp"

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
		if (t_entity == nullptr)
			throw("The entity you are trying to access is not initialised! ");
		else
			m_entities.insert_or_assign(t_name, t_entity);
	}

	void State::ResizeSceneView(unsigned int t_width, unsigned int t_height)
	{
		int newH = (1366 * t_height) / t_width;
		int displace = (newH - 768) / (-2);
		m_view = sf::View(sf::FloatRect(0, displace, 1366, newH));
	}

	sf::View State::GetSceneView()
	{
		return m_view;
	}

} }