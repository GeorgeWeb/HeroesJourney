#include "GUIElement.hpp"
#include <memory>

namespace Engine { namespace GUI {

	GUIElement::GUIElement(const sf::Vector2f& t_size)
		: Entity::Entity(std::make_unique<sf::RectangleShape>(sf::RectangleShape(t_size)))
	{ }

	void GUIElement::Update(const float t_deltaTime)
	{
		Entity::Entity::Update(t_deltaTime);
	}

} }