#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include <memory>

namespace Engine { namespace Entity {

	// Entity class interface and base functionality
	class Entity
	{
		protected:
			std::unique_ptr<sf::Shape> m_shape;
			sf::Vector2f m_position;
			Entity(std::unique_ptr<sf::Shape> t_shape);
		
		public:
			Entity() = delete;
			virtual ~Entity() = default;

		public:
			virtual void Update(const float t_deltaTime) { m_shape->setPosition(m_position); }

			inline void SetPosition(const sf::Vector2f& t_position) { m_position = t_position; }
			inline void Move(const sf::Vector2f& t_position) { m_position += t_position; }

			void SetTexture(const sf::Texture& t_texture, const sf::IntRect t_rect = /*:default:*/sf::IntRect(10, 10, 100, 100));

			// const accessors to the properties that can be used within the game window
			const sf::Vector2f position = m_position;
			const sf::Shape& shape = *m_shape; ///> used for easy drawing from the game data->window
	};

} }

#endif // !ENTITY_H
