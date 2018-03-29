#include "Infirmary.hpp"

namespace HJ {	namespace Entities {

	Infirmary::Infirmary(const std::string & t_sprite) :
		Building(t_sprite)
	{
		m_level = 1;
		m_bonus = m_level * 10;
	
	}

	Infirmary* Infirmary::GetType()
	{
		return this;
	}

	void Infirmary::Init()
	{
		Building::Init();
	}

	void Infirmary::Update(float t_deltaTime)
	{
		Building::Update(t_deltaTime);
		auto infComp = m_spriteComp;

		
	}

	void Infirmary::Render()
	{
		Building::Render();
	}

	void Infirmary::Upgrade()
	{
		m_bonus = m_level * 10;
		m_level += 1;
	}

	void Infirmary::ApplyBonus(std::vector<std::shared_ptr <Hero>> t_heroes)
	{
		for (auto hero : t_heroes)
		{
			if (hero->GetHealth() == hero->GetMaxHealth())
			{
				hero->SetMaxHealth(hero->GetMaxHealth() + m_bonus);
				hero->SetHealth(hero->GetMaxHealth());
			}
			else 
			{
				hero->SetMaxHealth(hero->GetMaxHealth() + m_bonus);
			}
			
			
		}
	}

} }