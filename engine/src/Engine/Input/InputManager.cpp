#include "InputManager.hpp"

namespace Engine { namespace Input {

	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& t_window) const
	{
		return sf::Mouse::getPosition(t_window);
	}

} }