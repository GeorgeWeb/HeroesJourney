#ifndef EVIL_AI_H
#define EVIL_AI_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/AnimatorComponent.hpp>
#include "../Components/StatusComponent.hpp"
#include "../Components/StateMachineComponent.hpp"

#include <functional>

namespace HJ { namespace Entities {

	class EvilAI : public Engine::ECM::Entity
	{
		private:
			std::shared_ptr<Engine::Components::SpriteComponent> m_spriteComp;
			std::shared_ptr<Engine::Components::AnimatorComponent> m_animatorComp;
			std::shared_ptr<Components::StatusComponent> m_statusComp;
			std::shared_ptr<Components::StateMachineComponent> m_smComp;

			int m_health;
			int m_maxHealth;
			unsigned int m_damage;
			unsigned int m_armour;

			std::string m_name;

		public:
			inline int GetHealth() { return m_health; }
			inline void SetHealth(const int t_health) { m_health = t_health; }
			inline int GetMaxHealth() { return m_maxHealth; }
			inline void SetMaxHealth(const int t_maxHealth) { m_maxHealth = t_maxHealth; }
			inline int GetDmg() { return m_damage; }
			inline void SetDmg(const int t_damage) { m_damage = t_damage; }
			inline int GetArmour() { return m_armour; }

			void TakeDamage(unsigned int t_dmg);

		public:
			std::shared_ptr<Engine::Components::SpriteComponent> GetSpriteComponent();
			std::shared_ptr<Engine::Components::AnimatorComponent> GetAnimatorComponent();
			std::shared_ptr<Components::StatusComponent> GetStatusComponent();
			std::shared_ptr<Components::StateMachineComponent> GetSMComponent();

			const std::string className() const override final { return m_name; }

		public:
			EvilAI(const std::string t_name, unsigned int t_health, unsigned int t_damage, unsigned int t_armour);
			virtual ~EvilAI() = default;

			EvilAI* GetType() override;

			void Init() override;
			void Update(float t_deltaTime) override;
			void Render() override;

			void SetSprite(const sf::Texture& t_texture, sf::IntRect t_texRect);
	};

} }

#endif // !EVIL_AI_H