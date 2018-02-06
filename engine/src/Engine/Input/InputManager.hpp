#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Graphics.hpp>
#include "../Entity/EntityManager.hpp"

namespace Engine { namespace Input {

	class InputManager final
	{
		public:
			InputManager() = default;
			~InputManager() = default;

			bool isClicked(std::shared_ptr<Entity::Entity> t_entity, sf::Mouse::Button t_button, sf::RenderWindow& t_window);
			bool isMouseOver(std::shared_ptr<Entity::Entity> t_entity, sf::Vector2i t_mousePos, sf::RenderWindow& t_window);
			inline sf::Vector2i GetMousePosition(sf::RenderWindow& t_window) const { return sf::Mouse::getPosition(t_window); }
			
		private:
			sf::Clock m_pressDelay;
	};

} }

#endif // !INPUT_MANAGER_H