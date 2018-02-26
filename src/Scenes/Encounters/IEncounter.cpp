#include "IEncounter.hpp"

namespace HJ { namespace Encounters {

	IEncounter::IEncounter(GameDataRef t_data) :
		m_data(t_data)
	{ }

	void IEncounter::Init()
	{
		// Implement
	}

	void IEncounter::HandleInput()
	{
		// Implement
	}

	void IEncounter::Update(float t_delatTime)
	{
		// Implement
	}

	void IEncounter::Draw(float t_deltaTime)
	{
		// Implement
	}

} }