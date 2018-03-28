#include "Library.hpp"

namespace HJ {	namespace Entities {

	Library::Library(const std::string & t_sprite) :
		Building(t_sprite)
	{
		m_level = 1;
		m_bonus = m_level * 10;
	

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

} }