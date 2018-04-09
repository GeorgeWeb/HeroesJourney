#include "BaseStates.hpp"

#include <iostream>

namespace HJ { namespace States {
	
	void BaseIdleState::EnterState(ECM::Entity* t_owner)
	{
		std::cout << "Waiting for turn.\n";
		// Set IsInTransition to false
		m_SM->SetInTransition(false);
	}

	void BaseIdleState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		if (m_SM->IsInTransition())
			m_SM->ChangeState("ChooseTarget");
	}

	void BaseChooseTargetState::EnterState(ECM::Entity* t_owner)
	{
		m_canChoose = true;
		m_chooseFinished = false;
	}

	void BaseChooseTargetState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		// use t_owner->className() for heuristics
	}
	
	void BaseStepInState::EnterState(ECM::Entity* t_owner)
	{
		std::cout << "Stepping in.\n";
		m_canStepIn = true;
	}

	void BaseStepInState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		if (m_canStepIn)
			t_owner->Move(sf::Vector2f(-m_speed, 0.0f));

		// exit state check
		if (t_owner->GetPosition().x <= m_position.x)
			m_canStepIn = false;

		// change state to attack condition
		if (!m_canStepIn)
		{
			auto sm = t_owner->GetComponent<Components::StateMachineComponent>("C_StateMachine");
			sm->ChangeState("Attack");
		}
	}

	void BaseAttackState::EnterState(ECM::Entity* t_owner)
	{
		std::cout << "Attacking.\n";
		m_isAttacking = true;
	}

	void BaseAttackState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		if (m_isAttacking)
		{
			for (auto hero : m_heroes)
			{
				auto dmg = (hero->GetArmour() >= m_damage) ? 0 : m_damage - hero->GetArmour();
				hero->TakeDamage(dmg);
				//std::cout << "DMG taken: " << dmg << std::endl;
				//std::cout << "HP: " << hero->GetHealth() << "/" << hero->GetMaxHealth() << std::endl;
				std::cout << std::endl;
			}
			m_isAttacking = false;
		}
		
		// change state to return condition
		if (!m_isAttacking)
		{
			auto sm = t_owner->GetComponent<Components::StateMachineComponent>("C_StateMachine");
			sm->ChangeState("Return");
		}
		
		// first DO checks (e.g. hp < half) and change state to rage if appropriate

		// if no need to rage:
		// Use heroes TakeDmgComponent
		// e.g. hero[i]->GetComponent<TakeDmgComponent>("...")->Receive(m_damage);
		// Take damage component checks for armors/resist/block chances and handles the logic and damage application
	}

	void BaseStepBackState::EnterState(ECM::Entity* t_owner)
	{
		std::cout << "Stepping back.\n";
		m_canStepBack = true;
	}

	void BaseStepBackState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		if (m_canStepBack)
			t_owner->Move(sf::Vector2f(m_speed, 0.0f));

		// exit state check
		if (t_owner->GetPosition().x >= m_position.x)
		{
			// reset to initial position if not accurately there
			t_owner->SetPosition(m_position);
			m_canStepBack = false;
		}

		// change state to wait condition
		if (!m_canStepBack)
		{
			auto sm = t_owner->GetComponent<Components::StateMachineComponent>("C_StateMachine");
			sm->ChangeState("Wait");
		}
	}

	void BaseFinishState::EnterState(ECM::Entity* t_owner)
	{
		
	}

	void BaseFinishState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
	}

	void States::BaseNearTargetState::EnterState(ECM::Entity* t_owner)
	{

	}

	void States::BaseNearTargetState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{

	}

} }