#include "Blacksmith.hpp"

namespace HJ { namespace Entities {

	Blacksmith::Blacksmith(const std::string & t_sprite) :
		Building(t_sprite)
	{
		m_level = 1;
		m_bonus = m_level * 10;
		isClicked = false;
		unClick = false;
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

		if (isClicked && !unClick)
		{
			blacksmithComp->GetSprite().setColor(sf::Color(blacksmithComp->GetSprite().getColor().r - 100,
				blacksmithComp->GetSprite().getColor().g - 100,
				blacksmithComp->GetSprite().getColor().b - 100,
				blacksmithComp->GetSprite().getColor().a));
			unClick = true;
		}

		if (unClick)
		{
			m_time -= t_deltaTime;
		}
		if (m_time <0.0f && unClick)
		{
			blacksmithComp->GetSprite().setColor(sf::Color(
				blacksmithComp->GetSprite().getColor().r + 100,
				blacksmithComp->GetSprite().getColor().g + 100,
				blacksmithComp->GetSprite().getColor().b + 100,
				blacksmithComp->GetSprite().getColor().a
			));

			m_time = 0.1f;
			unClick = false;
			isClicked = false;
		}
	}

	void Blacksmith::Render()
	{
		Building::Render();
	}

	void Blacksmith::Upgrade()
	{
		Building::Upgrade();
	}

} }