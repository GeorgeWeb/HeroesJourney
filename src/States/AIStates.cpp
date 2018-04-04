#include "AIStates.hpp"

namespace HJ { namespace States {
	
	void GolemMoveState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		// MOVE FORWARD LOGIC
		
		// change state to return
	}

	void GolemReturnState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		// MOVE BACK LOGIC

		// change state to attack
	}

	void GolemAttackState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		// first DO checks (e.g. hp < half) and change state to rage if appropriate

		// if no need to rage:
		// Use heroes TakeDmgComponent
		// e.g. hero[i]->GetComponent<TakeDmgComponent>("...")->Receive(m_damage);
		// Take damage component checks for armors/resist/block chances and handles the logic and damage application
	}

	void GolemRageState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		// Fundamentally, use heroes TakeDmgComponent
		// e.g. hero[i]->GetComponent<TakeDmgComponent>("...")->Receive(m_damage);
		// Take damage component checks for armors/resist/block chances and handles the logic and damage application

		// But DO apply conditions to the heroes as well! Main point of the Raging state!
	}

} }