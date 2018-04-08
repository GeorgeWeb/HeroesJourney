#include "GeneralStore.hpp"

namespace HJ { namespace Entities {

	GeneralStore::GeneralStore() : Building()
	{
		m_level = 1;
		m_bonus = 1;
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
	}

	void GeneralStore::Render()
	{
		Building::Render();
	}

} }