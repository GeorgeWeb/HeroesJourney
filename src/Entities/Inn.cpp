#include "Inn.hpp"

namespace HJ { namespace Entities {

	Inn::Inn(const std::string & t_sprite) :
		Building(t_sprite)
	{
		m_level = 1;
		m_bonus = m_level * 10;
		
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
		m_bonus = m_level * 10;
		m_level += 1;
	}

} }