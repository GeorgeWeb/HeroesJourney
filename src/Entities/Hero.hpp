#ifndef HERO_ENTITY_H
#define HERO_ENTITY_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/AnimatorComponent.hpp>
#include "../Components/StatusComponent.hpp"
#include "../Components/SkillComponent.hpp"

#include "EvilAI.hpp"

#include <functional>

namespace HJ { namespace Entities {

	class Hero : public Engine::ECM::Entity
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
			std::shared_ptr<Engine::Components::SpriteComponent> GetSpriteComponent();
			std::shared_ptr<Engine::Components::AnimatorComponent> GetAnimatorComponent();
			std::shared_ptr<Components::StatusComponent> GetStatusComponent();
			
			virtual const std::string className() const { return "Hero"; }

		public:
			Hero();
			virtual ~Hero() = default;

			virtual Hero* GetType() override;

			virtual void Init() override;
			virtual void Update(float t_deltaTime) override;
			virtual void Render() override;

			// can be applied to enemies
			void ExecuteSkill(std::shared_ptr<Skill> t_skill, std::shared_ptr<EvilAI> t_enemy);
			// can be applied to party members (used from Bard)
			void ExecuteSkill(std::shared_ptr<Skill> t_skill, std::vector<std::shared_ptr<Hero>> t_heroes);

			void SetSprite(const sf::Texture& t_texture, sf::IntRect t_texRect);
			void Animate(const std::string& t_animationName);
	};

} }

#endif // !HERO_ENTITY_H
