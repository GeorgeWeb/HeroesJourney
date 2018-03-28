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
		ResizeSceneView();
	}

	void State::ResizeSceneView()
	{
		// TODO: Change to use DEFAULTS when implemented in Settings class.
		float newScaleX = Engine2D::GetWin().getSize().x / static_cast<float>(1366);
		float newScaleY = Engine2D::GetWin().getSize().y / static_cast<float>(768);

		// SET VIEWPORT TO THE MOST RECENT SCALE OFFSETS AND RESIZE WINDOW
		m_view.setViewport(sf::FloatRect(0.0f, 0.0f, newScaleX, newScaleY));
		m_view.reset(sf::FloatRect(0.0f, 0.0f, (float)Engine2D::GetWin().getSize().x, (float)Engine2D::GetWin().getSize().y));
		Engine2D::GetWin().setSize(sf::Vector2u(m_view.getSize()));

		// CALCULATE THE NEW SCALE OFFSET
		newScaleX = Engine2D::GetWin().getSize().x / static_cast<float>(1366);
		newScaleY = Engine2D::GetWin().getSize().y / static_cast<float>(768);

		// CHECK FOR A LESS THAN DEFAULT RESOLUTION RESIZING (& reset to scale offset 1.0f)
		if (newScaleX < 1.0f) newScaleX = 1.0f;
		if (newScaleY < 1.0f) newScaleY = 1.0f;
		
		// SET VIEWPORT TO THE MOST RECENT SCALE OFFSETS AND RESIZE WINDOW
		m_view.setViewport(sf::FloatRect(0.0f, 0.0f, newScaleX, newScaleY));
		m_view.reset(sf::FloatRect(0.0f, 0.0f, (float)Engine2D::GetWin().getSize().x, (float)Engine2D::GetWin().getSize().y));
		Engine2D::GetWin().setSize(sf::Vector2u(m_view.getSize()));

		/** NOTE: 
		 ** Works fine and is the only way I could come up with for half a night. 
		 ** No more time to loose on it, doe it's not perfect (unlaggy).
		 **/
	}

	sf::View State::GetSceneView()
	{
		return m_view;
	}

} }