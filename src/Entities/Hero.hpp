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
			int m_maxHealth;
			int m_mana;
			int m_maxMana;
			unsigned int m_damage;
			unsigned int m_armour;
			unsigned int m_critChance;
			unsigned int m_dodgeChance;

			bool m_isStunned;
			bool m_isFlaming;
			bool m_isFrozen;
			
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
			Hero(const std::string& t_sprite);
			Hero(const std::string& t_sprite, const std::string& t_animator);
			virtual ~Hero() = default;

			virtual Hero* GetType() override;

			virtual void Init() override;
			virtual void Update(float t_deltaTime) override;
			virtual void Render() override;

			virtual void Attack(std::shared_ptr<EvilAI> t_enemy) = 0;
			virtual void Defend() = 0;

			// can be applied to enemies
			virtual void UseSkill1(std::shared_ptr<EvilAI> t_enemy) {};
			// can be applied to party members (used from Bard)
			virtual void UseSkill1(std::vector<std::shared_ptr<Hero>> t_heroes) {};
			// can be applied to enemies
			virtual void UseSkill2(std::shared_ptr<EvilAI> t_enemy) {};
			// can be applied to party members (used from Bard)
			virtual void UseSkill2(std::vector<std::shared_ptr<Hero>> t_heroes) {};

			void SetSprite(const sf::Texture& t_texture, sf::IntRect t_texRect);
			void Animate(const std::string& t_animationName);
	};

} }

#endif // !HERO_ENTITY_H
