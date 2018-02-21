#include "Rogue.hpp"

namespace HJ {
	namespace Entities {

		Rogue::Rogue(const std::string & t_sprite, const std::string & t_animator) :
			Hero(t_sprite, t_animator)
		{
			m_health = 75;
			m_mana = 75;
			m_armour = 10;
			m_damage = 30;
			m_alive = true;
			m_dodgeChance = 4;
			m_critChance = 4;
			m_isFlaming = false;
			m_isStunned = false;
		}

		void Rogue::Init(const sf::Texture& t_texture, sf::IntRect t_texRect)
		{
			Hero::Init(t_texture, t_texRect);
		}

		void Rogue::Update(float t_deltaTime)
		{
			Hero::Update(t_deltaTime);
		}

		void Rogue::Render()
		{
			Hero::Render();
		}

		void Rogue::Attack()
		{
			// implement
		}

		void Rogue::Skill(std::function<void()> t_func)
		{
			Hero::Skill(t_func);
		}

		void Rogue::Defend()
		{
			// implement
		}

		void Rogue::TrueMark()
		{
			// todo
		}

		void Rogue::StormOfDaggers()
		{
			// todo
		}

	}
}