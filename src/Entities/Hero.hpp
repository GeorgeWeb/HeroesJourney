#ifndef HERO_ENTITY_H
#define HERO_ENTITY_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/AnimatorComponent.hpp>

#include "EvilAI.hpp"

#include <functional>

namespace HJ { namespace Entities {

	class Hero : public Engine::ECM::Entity
	{
		private:
			std::shared_ptr<Engine::Components::SpriteComponent> m_spriteComp;
			std::shared_ptr<Engine::Components::AnimatorComponent> m_animatorComp;

		protected:
			int m_health;
			unsigned int m_mana;
			unsigned int m_damage;
			unsigned int m_armour;
			unsigned int m_critChance;
			unsigned int m_dodgeChance;

			bool m_isStunned;
			bool m_isFlaming;
			bool m_isFrozen;
			

		public:
			inline void SetHealth(const int t_health) { m_health = t_health; }
			inline void SetStunned(const bool t_stun) { m_isStunned = t_stun; }
			inline bool IsStunned() const { return m_isStunned; }
			inline void SetFlaming(const bool t_flame) { m_isFlaming = t_flame; }
			inline bool IsFlaming() const { return m_isFlaming; }
			inline void SetFrozen(const bool t_freeze) { m_isFrozen = t_freeze; }
			inline bool IsFrozen()const { return m_isFrozen; }


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

			virtual void Attack() = 0;
			virtual void Skill(std::function<void()> t_func);
			virtual void Defend() = 0;

			void SetSprite(const sf::Texture& t_texture, sf::IntRect t_texRect);
			void Animate(const std::string& t_animationName);
	};

} }

#endif // !HERO_ENTITY_H
