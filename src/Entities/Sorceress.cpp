#include "Sorceress.hpp"

namespace HJ {namespace Entities {

	Sorceress::Sorceress(bool t_populate) : Hero(t_populate)
	{
		m_name = "Sorceress";
		m_type = HERO_TYPE::GOOD;
		m_alive = true;
		if (t_populate)
		{
			m_health = 75;
			m_maxHealth = 75;
			m_mana = 120;
			m_maxMana = 120;
			m_armour = 5;
			m_damage = 30;
			m_dodgeChance = 10;
			m_critChance = 20;
		}
	}

	Sorceress* Sorceress::GetType()
	{
		return this;
	}

	void Sorceress::Init()
	{
		Hero::Init();

		// Add skills
		m_skillComp->AddSkill(SKILL_NAME::BASIC_ATTACK, std::make_shared<BasicAttack>());
		m_skillComp->AddSkill(SKILL_NAME::BASIC_DEFENCE, std::make_shared<BasicDefence>());
		m_skillComp->AddSkill(SKILL_NAME::SPECIAL_SKILL_1, std::make_shared<FireBolt>());
		m_skillComp->AddSkill(SKILL_NAME::SPECIAL_SKILL_2, std::make_shared<FrostAura>());
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