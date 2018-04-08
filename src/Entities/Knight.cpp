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
	}

	void Knight::Update(float t_deltaTime)
	{
		Hero::Update(t_deltaTime);
	}

	void Knight::Render()
	{
		Hero::Render();
	}

	void Knight::Attack(std::shared_ptr<EvilAI> t_enemy)
	{
		Hero::Attack(t_enemy);
	}

	void Knight::Defend()
	{
		Hero::Defend();
	}

	void Knight::UseSkill1(std::shared_ptr<EvilAI> t_enemy)
	{
		// implement
	}

	void Knight::UseSkill2(std::shared_ptr<EvilAI> t_enemy)
	{
		// implement
	}

} }