#include "Knight.hpp"

namespace HJ { namespace Entities {

	Knight::Knight(const std::string & t_sprite) :
		Hero(t_sprite)
	{
		m_health = 150;
		m_maxHealth = 150;
		m_mana = 75;
		m_maxMana = 75;
		m_armour = 20;
		m_damage = 50;
		m_alive = true;
		m_dodgeChance = 2;
		m_critChance = 3;
		m_isFlaming = false;
		m_isStunned = false;
	}

	Knight::Knight(const std::string & t_sprite, const std::string & t_animator) :
		Hero(t_sprite, t_animator)
	{ 
		m_health = 150;
		m_maxHealth = 150;
		m_mana = 75;
		m_maxMana = 75;
		m_armour = 20;
		m_damage = 50;
		m_alive = true;
		m_dodgeChance = 2;
		m_critChance = 3;
		m_isFlaming = false;
		m_isStunned = false;
	}

	Knight* Knight::GetType()
	{
		return this;
	}

	void Knight::Init()
	{
		Hero::Init();
	}

	void Knight::Update(float t_deltaTime)
	{
		Hero::Update(t_deltaTime);
	}

	void Knight::Render()
	{
		Hero::Render();
	}

	void Knight::Attack()
	{
		// implement
	}

	void Knight::Skill(std::function<void()> t_func)
	{
		Hero::Skill(t_func);
	}

	void Knight::Defend()
	{
		// implement
	}

	void Knight::HeroSlash()
	{
		// implement
	}

	void Knight::ShoulderBash()
	{
		// implement
	}

} }