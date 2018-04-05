#include "Rogue.hpp"

namespace HJ { namespace Entities {

	Rogue::Rogue(const std::string & t_sprite) :
		Hero(t_sprite)
	{
		m_health = 75;
		m_maxHealth = 75;
		m_mana = 75;
		m_maxMana = 75;
		m_armour = 10;
		m_damage = 30;
		m_alive = true;
		m_dodgeChance = 4;
		m_critChance = 4;
		m_isFlaming = false;
		m_isStunned = false;
	}

	Rogue::Rogue(const std::string & t_sprite, const std::string& t_animator) :
		Hero(t_sprite, t_animator)
	{
		m_health = 75;
		m_maxHealth = 75;
		m_mana = 75;
		m_maxMana = 75;
		m_armour = 10;
		m_damage = 30;
		m_alive = true;
		m_dodgeChance = 4;
		m_critChance = 4;
		m_isFlaming = false;
		m_isStunned = false;
	}

	Rogue* Rogue::GetType()
	{
		return this;
	}

	void Rogue::Init()
	{
		Hero::Init();
	}

	void Rogue::Update(float t_deltaTime)
	{
		Hero::Update(t_deltaTime);
	}

	void Rogue::Render()
	{
		Hero::Render();
	}

	void Rogue::Attack(std::shared_ptr<EvilAI> t_enemy)
	{
		Hero::Attack(t_enemy);
	}

	void Rogue::Defend()
	{
		Hero::Defend();
	}

	void Rogue::UseSkill1(std::shared_ptr<EvilAI> t_enemy)
	{
		// implement
	}

	void Rogue::UseSkill2(std::shared_ptr<EvilAI> t_enemy)
	{
		// implement
	}

} }