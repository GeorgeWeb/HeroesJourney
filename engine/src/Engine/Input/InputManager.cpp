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

	sf::Vector2i InputManager::GetJoystickPosition() const
	{
		return sf::Vector2i(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y));
	}

	sf::Vector2f InputManager::GetJoystickPositionToWorld(sf::RenderWindow& t_window) const
	{
		auto joystick = GetJoystickPosition();
		return t_window.mapPixelToCoords(joystick);
	}

} }