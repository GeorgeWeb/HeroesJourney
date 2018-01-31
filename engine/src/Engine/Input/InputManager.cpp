#include "InputManager.hpp"

namespace Engine { namespace Input {

	bool InputManager::isSpriteClicked(const sf::Sprite& t_object, sf::Mouse::Button t_button, sf::RenderWindow& t_window)
	{
		if (m_pressDelay.getElapsedTime().asSeconds() > 1.0f)
		{
			if (sf::Mouse::isButtonPressed(t_button) && t_button == sf::Mouse::Left)
			{
				sf::IntRect rect(t_object.getPosition().x, t_object.getPosition().y, // position
					t_object.getGlobalBounds().width, t_object.getGlobalBounds().height); // dimensions

				if (rect.contains(sf::Mouse::getPosition(t_window)))
				{
					m_pressDelay.restart();
					return true;
				}
			}
		}

		return false;
	}

} }