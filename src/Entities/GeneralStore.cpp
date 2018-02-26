#include "GeneralStore.hpp"

namespace HJ { namespace Entities {

	GeneralStore::GeneralStore(const std::string & t_sprite) :
		Building(t_sprite)
	{
		m_level = 1;
		m_bonus = 1;
		isClicked = false;
		unClick = false;
	}

	GeneralStore* GeneralStore::GetType()
	{
		return this;
	}

	void GeneralStore::Init()
	{
		Building::Init();
	}

	void GeneralStore::Update(float t_deltaTime)
	{
		Building::Update(t_deltaTime);

		auto genStoreComp = m_spriteComp;

		if (isClicked && !unClick)
		{
			genStoreComp->GetSprite().setColor(sf::Color(
				genStoreComp->GetSprite().getColor().r - 100,
				genStoreComp->GetSprite().getColor().g - 100,
				genStoreComp->GetSprite().getColor().b - 100,
				genStoreComp->GetSprite().getColor().a)
			);
			
			unClick = true;
		}

		if (unClick)
		{
			m_time -= t_deltaTime;
		}
		if (m_time < 0.0f && unClick)
		{
			genStoreComp->GetSprite().setColor(sf::Color(
				genStoreComp->GetSprite().getColor().r + 100,
				genStoreComp->GetSprite().getColor().g + 100,
				genStoreComp->GetSprite().getColor().b + 100,
				genStoreComp->GetSprite().getColor().a)
			);

			m_time = 0.1f;
			unClick = false;
			isClicked = false;
		}
	}

	void GeneralStore::Render()
	{
		Building::Render();
	}

} }