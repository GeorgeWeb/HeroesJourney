#include "Entity.hpp"

namespace Engine { namespace Entity {

	Entity::Entity(std::unique_ptr<sf::Shape> t_shape) 
		: m_shape(std::move(t_shape))
	{ }

	void Entity::SetTexture(const sf::Texture& t_texture, const sf::IntRect t_rect)
	{
		m_shape->setTexture(&t_texture);
		m_shape->setTextureRect(t_rect);
	}

} }