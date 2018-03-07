#include "Infirmary.hpp"

namespace HJ {	namespace Entities {

	Infirmary::Infirmary(const std::string & t_sprite) :
		Building(t_sprite)
	{
		m_level = 1;
		m_bonus = m_level * 10;
		isClicked = false;
		unClick = false;
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

		if (isClicked && !unClick)
		{
			infComp->GetSprite().setColor(sf::Color(
				infComp->GetSprite().getColor().r - 100,
				infComp->GetSprite().getColor().g - 100,
				infComp->GetSprite().getColor().b - 100,
				infComp->GetSprite().getColor().a)
			);
			
			unClick = true;
		}

		if (unClick)
		{
			m_time -= t_deltaTime;
		}

		if (m_time < 0.0f && unClick)
		{
			infComp->GetSprite().setColor(sf::Color(
				infComp->GetSprite().getColor().r + 100,
				infComp->GetSprite().getColor().g + 100,
				infComp->GetSprite().getColor().b + 100,
				infComp->GetSprite().getColor().a)
			);

			m_time = 0.1f;
			unClick = false;
			isClicked = false;
		}
	}

	void Infirmary::Render()
	{
		Building::Render();
	}

	void Infirmary::Upgrade()
	{
		Building::Upgrade();
	}

} }