#include "Knight.hpp"

namespace HJ { namespace Entities {

	Knight::Knight(bool t_populate) : Hero(t_populate)
	{
		m_name = "Knight";
		m_type = HERO_TYPE::GOOD;
		m_alive = true;
		if (t_populate)
		{
			m_health = 150;
			m_maxHealth = 150;
			m_mana = 75;
			m_maxMana = 75;
			m_armour = 20;
			m_damage = 35;
			m_dodgeChance = 5;
			m_critChance = 30;
		}
	}

	Knight* Knight::GetType()
	{
		return this;
	}

	void Knight::Init()
	{
		Hero::Init();

		// Add skills
		m_skillComp->AddSkill(SKILL_NAME::BASIC_ATTACK, std::make_shared<BasicAttack>());
		m_skillComp->AddSkill(SKILL_NAME::BASIC_DEFENCE, std::make_shared<BasicDefence>());
		m_skillComp->AddSkill(SKILL_NAME::SPECIAL_SKILL_1, std::make_shared<HeroicStrike>());
		m_skillComp->AddSkill(SKILL_NAME::SPECIAL_SKILL_2, std::make_shared<ShieldThrow>());
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