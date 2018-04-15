#include "Inn.hpp"

namespace HJ { namespace Entities {

	Inn::Inn(bool t_populate) : Building(t_populate)
	{
		if (t_populate)
		{
			m_level = 1;
			m_bonus = m_level * 20;
		}
	}

	Inn* Inn::GetType()
	{
		return this;
	}

	void Inn::Init()
	{
		Building::Init();
	}

	void Inn::Update(float t_deltaTime)
	{
		Building::Update(t_deltaTime);

		auto innComp = m_spriteComp;

		
	}

	void Inn::Render()
	{
		Building::Render();
	}

	void Inn::Upgrade()
	{
		m_bonus = m_level * 20;
		m_level += 1;
	}

	void Inn::ApplyBonus(std::vector<std::shared_ptr <Hero>> t_heroes)
	{
		for (auto hero : t_heroes)
		{
			if (hero->GetHealth() + m_bonus > hero->GetMaxHealth())
			{
				hero->SetHealth(hero->GetMaxHealth());
			}
			else if (hero->GetHealth() + m_bonus <= hero->GetMaxHealth())
			{
				hero->SetHealth(hero->GetHealth() + m_bonus);
			}

			if (hero->GetMana() + m_bonus > hero->GetMaxMana())
			{
				hero->SetMana(hero->GetMaxMana());
			}
			else if (hero->GetMana() + m_bonus <= hero->GetMaxMana())
			{
				hero->SetMana(hero->GetMana() + m_bonus);
			}
		}
	}

} }