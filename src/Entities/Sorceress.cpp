#include "Sorceress.hpp"
namespace HJ {namespace Entities {

		HJ::Entities::Sorceress::Sorceress(const std::string & t_sprite, const std::string & t_animatior):
			Hero(t_sprite, t_animatior)
		{
			m_health = 75;
			m_mana = 120;
			m_armour = 5;
			m_damage = 30;
			m_alive = true;
			m_dodgeChance = 1;
			m_critChance = 2;
			m_isFlaming = false;
			m_isStunned = false;
		}

		void Sorceress::Init(const sf::Texture & t_texture, sf::IntRect t_texRect)
		{
			Hero::Init(t_texture, t_texRect);
		}

		void Sorceress::Update(float t_deltaTime)
		{
			Hero::Update(t_deltaTime);
		}

		void Sorceress::Render()
		{
			Hero::Render();
		}

		void Sorceress::Attack(std::shared_ptr<Entity> t_entity)
		{
		}

		void Sorceress::Skill(const std::function<void(std::shared_ptr<Entity>t_entity)>& t_func)
		{
			Hero::Skill(t_func);
		}

		void Sorceress::Defend()
		{
		}

		void Sorceress::StreamOfFire()
		{
		}

		void Sorceress::Ignite()
		{
		}
}	}