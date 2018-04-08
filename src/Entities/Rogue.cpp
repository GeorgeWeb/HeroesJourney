#include "Rogue.hpp"

namespace HJ { namespace Entities {

	Rogue::Rogue() : Hero()
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
	}

	Rogue* Rogue::GetType()
	{
		return this;
	}

	void Rogue::Init()
	{
		Hero::Init();

		// TODO: Add skills
	}

	void Rogue::Update(float t_deltaTime)
	{
		Hero::Update(t_deltaTime);
	}

	void Rogue::Render()
	{
		Hero::Render();
	}

} }