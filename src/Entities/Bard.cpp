#include "Bard.hpp"

namespace HJ { namespace Entities {

	Bard::Bard() : Hero()
	{
		m_name = "Bard";
		m_type = HERO_TYPE::GOOD;
		m_health = 100;
		m_maxHealth = 100;
		m_mana = 80;
		m_maxMana = 80;
		m_armour = 10;
		m_damage = 30;
		m_alive = true;
		m_dodgeChance = 30;
		m_critChance = 20;
	}

	Bard* Bard::GetType()
	{
		return this;
	}

	void Bard::Init()
	{
		Hero::Init();

		// Add skills
		m_skillComp->AddSkill(SKILL_NAME::BASIC_ATTACK, std::make_shared<BasicAttack>());
		m_skillComp->AddSkill(SKILL_NAME::BASIC_DEFENCE, std::make_shared<BasicDefence>());
		m_skillComp->AddSkill(SKILL_NAME::SPECIAL_SKILL_1, std::make_shared<OffenseAura>());
		m_skillComp->AddSkill(SKILL_NAME::SPECIAL_SKILL_2, std::make_shared<DeffenseAura>());
		// TODO: CHANGE
		m_skillComp->AddSkill(SKILL_NAME::SKILL_INCREASE_HP, std::make_shared<BasicDefence>());
		m_skillComp->AddSkill(SKILL_NAME::SKILL_INCREASE_MP, std::make_shared<BasicDefence>());
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