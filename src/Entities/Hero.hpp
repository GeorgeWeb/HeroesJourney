#ifndef HERO_ENTITY_H
#define HERO_ENTITY_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/AnimatorComponent.hpp>

namespace HJ { namespace Entities {

	enum class HeroAnimStates : char
	{
		FULL,
		IDLE,
		MOVE,
		ATTACK,
		VICTORY,
		SPEAK,
		DIE
	};

	enum class HeroAttackAnimStates : char
	{
		BASIC,
		SKILL1,
		SKILL2
	};

	class Hero final : public Engine::ECM::Entity
	{
		private:
			std::shared_ptr<Engine::Components::SpriteComponent> m_spriteComp;
			std::shared_ptr<Engine::Components::AnimatorComponent> m_animatorComp;

		public:
			Hero();
			~Hero() = default;

			std::shared_ptr<Engine::Components::SpriteComponent> GetSpriteComponent();
			std::shared_ptr<Engine::Components::AnimatorComponent> GetAnimatorComponent();

			void Update(float t_deltaTime) override;
			void Render() override;

			void SetSprite(const sf::Texture& t_texture, sf::IntRect t_texRect);

			void Animate();

			void Attack() {}
			void TakeDamage() {}
			void Die() {}
	};

} }

#endif // !HERO_ENTITY_H
