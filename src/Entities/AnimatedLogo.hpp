#ifndef ANIMATED_LOGO_ENTITY_H
#define ANIMATED_LOGO_ENTITY_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/AnimatorComponent.hpp>

namespace HJ { namespace Entities {

		class AnimatedLogo final : public Engine::ECM::Entity
		{
			private:
				std::shared_ptr<Engine::Components::SpriteComponent> m_spriteComp;
				std::shared_ptr<Engine::Components::AnimatorComponent> m_animatorComp;

			public:
				std::shared_ptr<Engine::Components::SpriteComponent> GetSpriteComponent();
				std::shared_ptr<Engine::Components::AnimatorComponent> GetAnimatorComponent();

			public:
				AnimatedLogo();
				~AnimatedLogo() = default;

				AnimatedLogo* GetType() override;

				void Init(const sf::Texture& t_texture, sf::IntRect t_texRect);
				void Update(float t_deltaTime) override;
				void Render() override;

				void SetSprite(const sf::Texture& t_texture, sf::IntRect t_texRect);

				void Animate(const std::string& t_animationName);
		};

} }

#endif // !ANIMATED_LOGO_ENTITY_H