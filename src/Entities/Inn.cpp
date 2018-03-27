#include "Inn.hpp"

namespace HJ { namespace Entities {

	Inn::Inn(const std::string & t_sprite) :
		Building(t_sprite)
	{
		m_level = 1;
		m_bonus = m_level * 10;
		isClicked = false;
		unClick = false;
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

		if (isClicked && !unClick)
		{
			innComp->GetSprite().setColor(sf::Color(innComp->GetSprite().getColor().r - 100,
				innComp->GetSprite().getColor().g - 100,
				innComp->GetSprite().getColor().b - 100,
				innComp->GetSprite().getColor().a));
			unClick = true;
		}

		if (unClick)
		{
			m_time -= t_deltaTime;
		}
		if (m_time <0.0f && unClick)
		{
			innComp->GetSprite().setColor(sf::Color(innComp->GetSprite().getColor().r + 100,
				innComp->GetSprite().getColor().g + 100,
				innComp->GetSprite().getColor().b + 100,
				innComp->GetSprite().getColor().a));

			m_time = 0.1f;
			unClick = false;
			isClicked = false;
		}
	}

	void Inn::Render()
	{
		Building::Render();
	}

	void Inn::Upgrade()
	{
		m_bonus = m_level * 10;
		m_level += 1;
	}

} }