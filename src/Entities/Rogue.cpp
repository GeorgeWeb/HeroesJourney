#include "Rogue.hpp"

namespace HJ { namespace Entities {

	Rogue::Rogue(bool t_populate) : Hero(t_populate)
	{
		m_name = "Rogue";
		m_type = HERO_TYPE::GOOD;
		m_alive = true;
		if (t_populate)
		{
			m_health = 75;
			m_maxHealth = 75;
			m_mana = 75;
			m_maxMana = 75;
			m_armour = 10;
			m_damage = 25;
			m_dodgeChance = 25;
			m_critChance = 40;
		}
	}

	Rogue* Rogue::GetType()
	{
		return this;
	}

	void Rogue::Init()
	{
		Hero::Init();

		// Add skills
		m_skillComp->AddSkill(SKILL_NAME::BASIC_ATTACK, std::make_shared<BasicAttack>());
		m_skillComp->AddSkill(SKILL_NAME::BASIC_DEFENCE, std::make_shared<BasicDefence>());
		m_skillComp->AddSkill(SKILL_NAME::SPECIAL_SKILL_1, std::make_shared<RavenBow>());
		m_skillComp->AddSkill(SKILL_NAME::SPECIAL_SKILL_2, std::make_shared<RainOfArrows>());
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