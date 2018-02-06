#include "InputManager.hpp"

namespace Engine { namespace Input {

	bool InputManager::isClicked(std::shared_ptr<Entity::Entity> t_entity, sf::Mouse::Button t_button, sf::RenderWindow& t_window)
	{
		if (m_pressDelay.getElapsedTime().asSeconds() > 1.0f)
		{
			if (sf::Mouse::isButtonPressed(t_button) && t_button == sf::Mouse::Left)
			{
				auto pos = static_cast<sf::Vector2i>(t_entity->GetPosition());
				auto size = sf::Vector2i(t_entity->GetShape().getGlobalBounds().width, t_entity->GetShape().getGlobalBounds().height);
				sf::IntRect rect(pos, size);

				if (rect.contains(sf::Mouse::getPosition(t_window)))
				{
					m_pressDelay.restart();
					return true;
				}
			}
		}

		return false;
	}

	bool InputManager::isMouseOver(std::shared_ptr<Entity::Entity> t_entity, sf::Vector2i t_mousePos, sf::RenderWindow& t_window)
	{
		return false;
	}

} }