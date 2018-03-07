#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../ECM.hpp"

namespace Engine { namespace Components {

	class SpriteComponent final : public ECM::Component
	{
		protected:
			std::shared_ptr<sf::Sprite> m_sprite;

		public:
			SpriteComponent() = delete;
			explicit SpriteComponent(ECM::Entity* t_parent);

			SpriteComponent* GetType() override;

			void Update(float t_deltaTime) override;
			void Render() override;

			sf::Sprite& GetSprite();
	};

} }

#endif // !SPRITE_COMPONENT_H