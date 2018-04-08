#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Graphics.hpp>

namespace Engine { namespace Input {

	class InputManager final
	{
		public:
			InputManager() = default;
			~InputManager() = default;

			sf::Vector2i GetMousePosition(sf::RenderWindow& t_window) const;
			sf::Vector2f GetMousePositionToWorld(sf::RenderWindow& t_window) const;

			template<class T>
			bool isClicked(const T& t_object, sf::Mouse::Button t_button, sf::RenderWindow& t_window)
			{
				static_assert(std::is_base_of<sf::Drawable, T>::value, "Must inherit from the SFML abstract class Drawable");
				// [time] wait time between mouse presses to prevent unwanted multiple clicking behaviour
				if (m_pressDelay.getElapsedTime().asSeconds() > 0.5f)
				{
					if (sf::Mouse::isButtonPressed(t_button) && t_button == sf::Mouse::Left)
					{
						auto mouse = GetMousePositionToWorld(t_window);
						auto bounds = t_object.getGlobalBounds();
						sf::FloatRect rect(bounds);
						if (rect.contains(mouse))
						{
							m_pressDelay.restart();
							return true;
						}
					}
				}

				return false;
			}

			//bool IsMouseOver(std::shared_ptr<ECM::Entity> t_entity, sf::Vector2i t_mousePos, sf::RenderWindow& t_window);
			
		private:
			sf::Clock m_pressDelay;
	};

} }

#endif // !INPUT_MANAGER_H