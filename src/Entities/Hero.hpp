#ifndef HERO_ENTITY_H
#define HERO_ENTITY_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/AnimatorComponent.hpp>
#include "../Components/StatusComponent.hpp"
#include "../Components/SkillComponent.hpp"

#include <functional>

namespace HJ { namespace Entities {
	
	enum class HERO_TYPE : int
	{
		GOOD = 0,
		EVIL = 1
	};

	class Hero : public Engine::ECM::Entity
	{
		protected:
			std::shared_ptr<Engine::Components::SpriteComponent> m_spriteComp;
			std::shared_ptr<Engine::Components::AnimatorComponent> m_animatorComp;
			std::shared_ptr<Components::StatusComponent> m_statusComp;
			std::shared_ptr<Components::SkillComponent> m_skillComp;

		public:
			std::shared_ptr<Engine::Components::SpriteComponent> GetSpriteComponent();
			std::shared_ptr<Engine::Components::AnimatorComponent> GetAnimatorComponent();
			std::shared_ptr<Components::StatusComponent> GetStatusComponent();
			std::shared_ptr<Components::SkillComponent> GetSkillComponent();

			virtual const std::string className() const override { return m_name; }
			virtual const HERO_TYPE heroType() const { return m_type; }

		protected:
			int m_health;
			int m_maxHealth;
			int m_mana;
			int m_maxMana;
			unsigned int m_damage;
			unsigned int m_armour;
			unsigned int m_critChance;
			unsigned int m_dodgeChance;

			std::string m_name;
			HERO_TYPE m_type;

		public:
			inline int GetHealth() const { return m_health; }
			inline void SetHealth(const int t_health) { m_health = t_health; }
			inline int GetMaxHealth() const { return m_maxHealth; }
			inline void SetMaxHealth(const int t_maxHealth) { m_maxHealth = t_maxHealth; }
			inline int GetMana() const { return m_mana; }
			inline void SetMana(const int t_mana) { m_mana = t_mana; }
			inline int GetMaxMana() const { return m_maxMana; }
			inline void SetMaxMana(const int t_maxMana) { m_maxMana = t_maxMana; }
			inline int GetDmg() const { return m_damage; }
			inline void SetDmg(const int t_damage) { m_damage = t_damage; }
			inline int GetCrit() const { return m_critChance; }
			inline int GetArmour() const { return m_armour; }
			inline int GetDodge() const { return m_dodgeChance; }

			void TakeDamage(unsigned int t_dmg);

		public:
			// default constructor (used for GOOD types)
			Hero();
			// default constructor (used for EVIL types)
			Hero(const std::string& t_name, HERO_TYPE t_type, unsigned int t_health, unsigned int t_damage, unsigned int t_armour);
			virtual ~Hero() = default;

			virtual Hero* GetType() override;

			virtual void Init() override;
			virtual void Update(float t_deltaTime) override;
			virtual void Render() override;

			void SetSprite(const sf::Texture& t_texture, sf::IntRect t_texRect);
			void Animate(const std::string& t_animationName);
	};

} }

#endif // !HERO_ENTITY_H
