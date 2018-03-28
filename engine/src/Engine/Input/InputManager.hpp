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

			template<class T>
			bool isClicked(const T& t_object, sf::Mouse::Button t_button, sf::RenderWindow& t_window)
			{
				static_assert(std::is_base_of<sf::Drawable, T>::value, "Must inherit from the SFML abstract class Drawable");
				// [time] wait time between mouse presses to prevent unwanted multiple clicking behaviour
				if (m_pressDelay.getElapsedTime().asSeconds() > 0.3f)
				{
					if (sf::Mouse::isButtonPressed(t_button) && t_button == sf::Mouse::Left)
					{
						// TODO: Change to use DEFAULTS when implemented in Settings class.
						float offsetX = Engine2D::GetWin().getSize().x / static_cast<float>(1366);
						float offsetY = Engine2D::GetWin().getSize().y / static_cast<float>(768);
						auto pos = static_cast<sf::Vector2i>(t_object.getPosition() * sf::Vector2f(offsetX, offsetY));
						auto size = sf::Vector2i(t_object.getGlobalBounds().width, t_object.getGlobalBounds().height);
						sf::IntRect rect(pos, size);

						if (rect.contains(GetMousePosition(t_window)))
						{
							m_pressDelay.restart();
							return true;
						}
					}
				}

				return false;
			}

			//bool isMouseOver(std::shared_ptr<ECM::Entity> t_entity, sf::Vector2i t_mousePos, sf::RenderWindow& t_window);
			
		private:
			sf::Clock m_pressDelay;
	};

} }

#endif // !INPUT_MANAGER_H