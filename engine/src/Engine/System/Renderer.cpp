#include "Renderer.hpp"
#include <iostream>

namespace Engine { namespace System {

	static std::queue<const sf::Drawable*> sprites;
	static sf::RenderWindow* rw;

	namespace Renderer
	{
		void Initialize(sf::RenderWindow& t_rw)
		{
			rw = &t_rw;
		}

		void Shutdown()
		{
			while (!sprites.empty())
				sprites.pop();
		}

		void Render()
		{
			if (!rw) throw("No render window set! ");

			while (!sprites.empty())
			{
				rw->draw(*sprites.front());
				sprites.pop();
			}
		}

		void Queue(const sf::Drawable* t_sp)
		{
			sprites.push(t_sp);
		}
	}

} }