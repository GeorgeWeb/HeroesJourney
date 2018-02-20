#ifndef HERO_ENTITY_H
#define HERO_ENTITY_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/AnimatorComponent.hpp>

#include <functional>

namespace HJ { namespace Entities {

	class Hero : public Engine::ECM::Entity
	{
		private:
			std::shared_ptr<Engine::Components::SpriteComponent> m_spriteComp;
			std::shared_ptr<Engine::Components::AnimatorComponent> m_animatorComp;

		public:
			std::shared_ptr<Engine::Components::SpriteComponent> GetSpriteComponent();
			std::shared_ptr<Engine::Components::AnimatorComponent> GetAnimatorComponent();

		public:
			Hero() = delete;
			Hero(const std::string& t_sprite, const std::string& t_animator);
			virtual ~Hero() = default;

			virtual void Init(const sf::Texture& t_texture, sf::IntRect t_texRect);

			virtual void Update(float t_deltaTime);
			virtual void Render();

			virtual void Attack(std::shared_ptr<Entity> t_entity) = 0;
			virtual void Skill(const std::function<void(std::shared_ptr<Entity> t_entity)>& t_func);
			virtual void Defend() = 0;

			void SetSprite(const sf::Texture& t_texture, sf::IntRect t_texRect);
			void Animate(const std::string& t_animationName);
	};

} }

#endif // !HERO_ENTITY_H
