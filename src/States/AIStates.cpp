#include "AIStates.hpp"

#include <iostream>

namespace HJ { namespace States {
	
	void GolemWaitState::EnterState(ECM::Entity* t_owner)
	{
		std::cout << "Waiting for turn.\n";
	}

	void GolemStepInState::EnterState(ECM::Entity * t_owner)
	{
		std::cout << "Stepping in.\n";
		m_canStepIn = true;
	}

	void GolemStepInState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		t_owner->Move(sf::Vector2f(-m_speed, 0.0f));
		
		// exit state check
		if (t_owner->GetPosition().x <= m_position.x)
			m_canStepIn = false;

		// change state to attack condition
		if (!m_canStepIn)
		{
			auto sm = t_owner->GetComponent<Components::StateMachineComponent>("C_FrostGolemSM");
			sm->ChangeState("Attack");
		}
	}

	void GolemReturnState::EnterState(ECM::Entity * t_owner)
	{
		std::cout << "Returning.\n";
		m_canReturn = true;
	}

	void GolemReturnState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		t_owner->Move(sf::Vector2f(m_speed, 0.0f));
		// exit state check
		if (t_owner->GetPosition().x == m_position.x)
		{
			// reset to initial position if not accurately there
			t_owner->SetPosition(m_position);
			m_canReturn = false;
		}
		
		// change state to wait condition
		if (!m_canReturn)
		{
			auto sm = t_owner->GetComponent<Components::StateMachineComponent>("C_FrostGolemSM");
			sm->ChangeState("Wait");
		}
	}

	void GolemAttackState::EnterState(ECM::Entity* t_owner)
	{
		m_isAttacking = true;
	}

	void GolemAttackState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		for (auto hero : m_heroes)
		{
			auto dmg = (hero->GetArmour() >= m_damage) ? 0 : m_damage - hero->GetArmour();
			hero->TakeDamage(dmg + 10);
			//std::cout << "DMG taken: " << dmg << std::endl;
			//std::cout << "HP: " << hero->GetHealth() << "/" << hero->GetMaxHealth() << std::endl;
			std::cout << std::endl;
		}
		m_isAttacking = false;
		
		// change state to return condition
		if (!m_isAttacking)
		{
			auto sm = t_owner->GetComponent<Components::StateMachineComponent>("C_FrostGolemSM");
			sm->ChangeState("Return");
		}
		
		// first DO checks (e.g. hp < half) and change state to rage if appropriate

		// if no need to rage:
		// Use heroes TakeDmgComponent
		// e.g. hero[i]->GetComponent<TakeDmgComponent>("...")->Receive(m_damage);
		// Take damage component checks for armors/resist/block chances and handles the logic and damage application
	}

	/* TIPS FOR RAGING STATE */
	// Fundamentally, use heroes TakeDmgComponent
	// e.g. hero[i]->GetComponent<TakeDmgComponent>("...")->Receive(m_damage);
	// Take damage component checks for armors/resist/block chances and handles the logic and damage application

	// But DO apply conditions to the heroes as well! Main point of the Raging state!


	//!!! ADD DIE STATE
} }