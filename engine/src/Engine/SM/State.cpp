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

	// Both functions below need rework!
	void State::InitSceneView()
	{
		m_view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
		m_view.setSize(Engine2D::GetWin().getSize().x, Engine2D::GetWin().getSize().y);
	}

	void State::ResizeSceneView(unsigned int t_width, unsigned int t_height)
	{
		sf::FloatRect visibleArea(0, 0, t_width, t_height);
		m_view.reset(visibleArea);
	}

	sf::View State::GetSceneView()
	{
		return m_view;
	}

} }