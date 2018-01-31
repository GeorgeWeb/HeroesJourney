#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Graphics.hpp>

namespace Engine { namespace Input {

	class InputManager final
	{
		public:
			InputManager() = default;
			~InputManager() = default;

			bool isSpriteClicked(const sf::Sprite& t_object, sf::Mouse::Button t_button, sf::RenderWindow& t_window);
			inline sf::Vector2i GetMousePosition(sf::RenderWindow& t_window) const { return sf::Mouse::getPosition(t_window); }
		
		private:
			sf::Clock m_pressDelay;
	};

} }

#endif // !INPUT_MANAGER_H