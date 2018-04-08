#ifndef EVIL_AI_H
#define EVIL_AI_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/AnimatorComponent.hpp>
#include "../Components/StatusComponent.hpp"

#include <functional>

namespace HJ { namespace Entities {

	class EvilAI : public Engine::ECM::Entity
	{
		private:
			std::shared_ptr<Engine::Components::SpriteComponent> m_spriteComp;
			std::shared_ptr<Engine::Components::AnimatorComponent> m_animatorComp;
			std::shared_ptr<Components::StatusComponent> m_statusComp;

		protected:
			int m_health;
			int m_maxHealth;
			int m_mana;
			int m_maxMana;
			unsigned int m_damage;
			unsigned int m_armour;
			unsigned int m_critChance;
			unsigned int m_dodgeChance;

		public:
			inline int GetHealth() { return m_health; }
			inline void SetHealth(const int t_health) { m_health = t_health; }
			inline int GetMaxHealth() { return m_maxHealth; }
			inline void SetMaxHealth(const int t_maxHealth) { m_maxHealth = t_maxHealth; }
			inline int GetMana() { return m_mana; }
			inline void SetMana(const int t_mana) { m_mana = t_mana; }
			inline int GetMaxMana() { return m_maxMana; }
			inline void SetMaxMana(const int t_maxMana) { m_maxMana = t_maxMana; }
			inline int GetDmg() { return m_damage; }
			inline void SetDmg(const int t_damage) { m_damage = t_damage; }
			inline int GetCrit() { return m_critChance; }
			inline int GetArmour() { return m_armour; }
			inline int GetDodge() { return m_dodgeChance; }

			void TakeDamage(unsigned int t_dmg);

		public:
			std::shared_ptr<Engine::Components::SpriteComponent> GetSpriteComponent();
			std::shared_ptr<Engine::Components::AnimatorComponent> GetAnimatorComponent();
			std::shared_ptr<Components::StatusComponent> GetStatusComponent();

			virtual const std::string className() const { return "Enemy AI"; }

		public:
			EvilAI();
			virtual ~EvilAI() = default;

			EvilAI* GetType() override;

			virtual void Init() override;
			virtual void Update(float t_deltaTime) override;
			virtual void Render() override;

			void SetSprite(const sf::Texture& t_texture, sf::IntRect t_texRect);
	};

} }

#endif // !EVIL_AI_H