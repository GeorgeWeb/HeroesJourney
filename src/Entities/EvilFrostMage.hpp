#ifndef EVIL_FROST_MAGE_H
#define EVIL_FROST_MAGE_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/AnimatorComponent.hpp>

#include "EvilAI.hpp"

#include <functional>

namespace HJ { namespace Entities {

		enum EvilMageBehaviour
		{
			// derived
			ATTACK = AIBehaviour::ATTACK,
			DEFEND = AIBehaviour::DEFEND,
			DIE = AIBehaviour::DIE,
			// new
			FROST_STORM,
			ICY_BURST
		};

		class EvilFrostMage : public EvilAI
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
			EvilFrostMage();
			EvilFrostMage(const std::string& t_sprite, const std::string& t_animator);
			virtual ~EvilFrostMage() = default;

			void Init(const sf::Texture& t_texture, sf::IntRect t_texRect) override;

			void Update(float t_deltaTime) override;
			void Render() override;

			void Attack(std::shared_ptr<Hero> t_hero) override;
			void Skill(std::function<void(std::shared_ptr<Hero>)> t_func) override;
			void Defend() override;
		};
	}
}

#endif // !EVIL_FROST_MAGE_H