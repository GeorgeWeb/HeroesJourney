#include "Bard.hpp"

namespace HJ { namespace Entities {

	Bard::Bard(bool t_populate) : Hero(t_populate)
	{
		m_name = "Bard";
		m_type = HERO_TYPE::GOOD;
		m_alive = true;
		if (t_populate)
		{
			m_health = 100;
			m_maxHealth = 100;
			m_mana = 80;
			m_maxMana = 80;
			m_armour = 10;
			m_damage = 15;
			m_dodgeChance = 15;
			m_critChance = 20;
		}
	}

	Bard* Bard::GetType()
	{
		return this;
	}

	void Bard::Init()
	{
		Hero::Init();

		// Add skills
		m_skillComp->AddSkill(SKILL_NAME::BASIC_ATTACK, std::make_shared<BasicMagicAttack>());
		m_skillComp->AddSkill(SKILL_NAME::BASIC_DEFENCE, std::make_shared<BasicDefence>());
		m_skillComp->AddSkill(SKILL_NAME::SPECIAL_SKILL_1, std::make_shared<OffenseAura>());
		m_skillComp->AddSkill(SKILL_NAME::SPECIAL_SKILL_2, std::make_shared<DeffenseAura>());
	}

	void Bard::Update(float t_deltaTime)
	{
		Hero::Update(t_deltaTime);
	}

	void Bard::Render()
	{
		Hero::Render();
	}

} }