#ifndef GUI_ELEMENT_HPP
#define GUI_ELEMENT_HPP

#include "../Entity/Entity.hpp"

namespace Engine { namespace GUI {

	class GUIElement : public Entity::Entity
	{
		public:
			GUIElement(const sf::Vector2f& t_size);

			void Update(const float t_deltaTime) override;
	};

} }

#endif // !GUI_ELEMENT_HPP