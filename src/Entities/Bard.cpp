#include "Bard.hpp"

namespace HJ { namespace Entities {

	Bard::Bard() : Hero()
	{
		m_health = 100;
		m_maxHealth = 100;
		m_mana = 80;
		m_maxMana = 80;
		m_armour = 10;
		m_damage = 30;
		m_alive = true;
		m_dodgeChance = 3;
		m_critChance = 2;
	}

	Bard* Bard::GetType()
	{
		return this;
	}

	void Bard::Init()
	{
		Hero::Init();
	}

	void Bard::Update(float t_deltaTime)
	{
		Hero::Update(t_deltaTime);
	}

	void Bard::Render()
	{
		Hero::Render();
	}

	void Bard::Attack(std::shared_ptr<EvilAI> t_enemy)
	{
		Hero::Attack(t_enemy);
	}

	void Bard::Defend()
	{
		Hero::Defend();
	}

	void Bard::UseSkill1(std::vector<std::shared_ptr<Hero>> t_heroes)
	{
		// implement
	}

	void Bard::UseSkill2(std::vector<std::shared_ptr<Hero>> t_heroes)
	{
		// implement
	}

} }