#include "Renderer.hpp"
#include <iostream>

namespace Engine { namespace System {

	static std::queue<const sf::Drawable*> sprites;
	static sf::RenderWindow* window;

	namespace Renderer
	{
		void Initialize(sf::RenderWindow& t_rw)
		{
			window = &t_rw;
		}

		sf::RenderWindow& GetWin()
		{
			return *window;
		}

		void Shutdown()
		{
			while (!sprites.empty())
				sprites.pop();
		}

		void Render()
		{
			if (!window) throw("No render window set! ");

			while (!sprites.empty())
			{
				window->draw(*sprites.front());
				sprites.pop();
			}
		}

		void Queue(const sf::Drawable* t_sp)
		{
			sprites.push(t_sp);
		}
	}

} }