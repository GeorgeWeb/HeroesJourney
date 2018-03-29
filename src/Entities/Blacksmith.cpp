#include "Blacksmith.hpp"

namespace HJ { namespace Entities {

	Blacksmith::Blacksmith(const std::string & t_sprite) :
		Building(t_sprite)
	{
		m_level = 1;
		m_bonus = m_level * 10;
		
	}

	Blacksmith* Blacksmith::GetType()
	{
		return this;
	}

	void Blacksmith::Init()
	{
		Building::Init();
	}

	void Blacksmith::Update(float t_deltaTime)
	{
		Building::Update(t_deltaTime);

		auto blacksmithComp = m_spriteComp;

		
	}

	void Blacksmith::Render()
	{
		Building::Render();
	}

	void Blacksmith::Upgrade()
	{
		m_bonus = m_level * 10;
		m_level += 1;
	}

	void Blacksmith::ApplyBonus(std::vector<std::shared_ptr <Hero>> t_heroes)
	{
		for (auto hero : t_heroes)
		{
			hero->SetDmg(hero->GetDmg() + m_bonus);
		}
	}

} }