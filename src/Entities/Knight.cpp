#include "Knight.hpp"

namespace HJ { namespace Entities {

	Knight::Knight() : Hero()
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
	}

	Knight* Knight::GetType()
	{
		return this;
	}

	void Knight::Init()
	{
		Hero::Init();

		// TODO: Add skills
	}

	void Knight::Update(float t_deltaTime)
	{
		Hero::Update(t_deltaTime);
	}

	void Knight::Render()
	{
		Hero::Render();
	}

} }