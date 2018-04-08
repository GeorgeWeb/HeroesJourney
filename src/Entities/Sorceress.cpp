#include "Sorceress.hpp"

namespace HJ {namespace Entities {

	Sorceress::Sorceress() : Hero()
	{
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
	}

	void Sorceress::Update(float t_deltaTime)
	{
		Hero::Update(t_deltaTime);
	}

	void Sorceress::Render()
	{
		Hero::Render();
	}

	void Sorceress::Attack(std::shared_ptr<EvilAI> t_enemy)
	{
		Hero::Attack(t_enemy);
	}

	void Sorceress::Defend()
	{
		Hero::Defend();
	}

	void Sorceress::UseSkill1(std::shared_ptr<EvilAI> t_enemy)
	{
		// implement
	}

	void Sorceress::UseSkill2(std::shared_ptr<EvilAI> t_enemy)
	{
		// implement
	}

} }