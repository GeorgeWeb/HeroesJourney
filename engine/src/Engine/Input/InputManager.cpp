#include "InputManager.hpp"

namespace Engine { namespace Input {

	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& t_window) const
	{
		return sf::Mouse::getPosition(t_window);
	}

	sf::Vector2f InputManager::GetMousePositionToWorld(sf::RenderWindow& t_window) const
	{
		auto mouse = GetMousePosition(t_window);
		return t_window.mapPixelToCoords(mouse);
	}

} }