#include "Library.hpp"

namespace HJ {	namespace Entities {

		Library::Library(const std::string & t_sprite) :
			Building(t_sprite)
		{
			m_level = 1;
			m_bonus = m_level * 10;
			isClicked = false;
			unClick = false;

		}

		Library* Library::GetType()
		{
			return this;
		}

		void Library::Init(const sf::Texture& t_texture)
		{
			Building::Init(t_texture);
		}

		void Library::Update(float t_deltaTime)
		{
			Building::Update(t_deltaTime);

			auto libraryComp = m_spriteComp;

			if (isClicked && !unClick)
			{
				libraryComp->GetSprite().setColor(sf::Color(libraryComp->GetSprite().getColor().r - 100,					libraryComp->GetSprite().getColor().g - 100,					libraryComp->GetSprite().getColor().b - 100,					libraryComp->GetSprite().getColor().a));				unClick = true;			}

			if (unClick)			{				m_time -= t_deltaTime;
			}			if (m_time <0.0f && unClick)			{
				libraryComp->GetSprite().setColor(sf::Color(libraryComp->GetSprite().getColor().r + 100,
					libraryComp->GetSprite().getColor().g + 100,
					libraryComp->GetSprite().getColor().b + 100,
					libraryComp->GetSprite().getColor().a));
				m_time = 0.1f;
				unClick = false;				isClicked = false;
			}
		}

		void Library::Render()
		{
			Building::Render();
		}

		void Library::Upgrade()
		{
			Building::Upgrade();
		}



	} }