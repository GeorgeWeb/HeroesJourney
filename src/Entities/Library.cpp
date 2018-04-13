#include "Library.hpp"

namespace HJ {	namespace Entities {

	Library::Library(bool t_populate) : Building(t_populate)
	{
		if (t_populate)
		{
			m_level = 1;
			m_bonus = m_level * 10;
		}
	}

	Library* Library::GetType()
	{
		return this;
	}

	void Library::Init()
	{
		Building::Init();
	}

	void Library::Update(float t_deltaTime)
	{
		Building::Update(t_deltaTime);

		auto libraryComp = m_spriteComp;

		
	}

	void Library::Render()
	{
		Building::Render();
	}

	void Library::Upgrade()
	{
		m_bonus = m_level * 10;
		m_level += 1;
	}

	void Library::ApplyBonus(std::vector<std::shared_ptr <Hero>> t_heroes)
	{
		for (auto hero : t_heroes)
		{
			if (hero->GetMana() == hero->GetMaxMana())
			{
				hero->SetMaxMana(hero->GetMaxMana() + m_bonus);
				hero->SetMana(hero->GetMaxMana());
			}
			else
			{
				hero->SetMaxMana(hero->GetMaxMana() + m_bonus);
			}
			
		}
		
	}

} }