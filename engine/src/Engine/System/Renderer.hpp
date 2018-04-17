#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <queue>

namespace Engine { namespace System {

	namespace Renderer
	{
		void Initialize(sf::RenderWindow& t_rw);

		void Shutdown();

		void Render();

		void Queue(const sf::Drawable* t_sp);
	}

} }

#endif // !RENDERER_H
