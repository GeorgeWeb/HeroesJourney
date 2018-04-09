#include "Sorceress.hpp"

namespace HJ {namespace Entities {

	Sorceress::Sorceress() : Hero()
	{
		m_name = "Sorceress";
		m_type = HERO_TYPE::GOOD;
		m_health = 75;
		m_maxHealth = 75;
		m_mana = 120;
		m_maxMana = 120;
		m_armour = 5;
		m_damage = 30;
		m_alive = true;
		m_dodgeChance = 1;
		m_critChance = 2;
	}

	Sorceress* Sorceress::GetType()
	{
		return this;
	}

	void Sorceress::Init()
	{
		Hero::Init();

		// TODO: Add skills
	}

	void Sorceress::Update(float t_deltaTime)
	{
		Hero::Update(t_deltaTime);
	}

	void Sorceress::Render()
	{
		Hero::Render();
	}

} }