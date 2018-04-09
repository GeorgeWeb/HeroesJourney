#include "ActionStates.hpp"

#include <iostream>

namespace HJ { namespace States {
	
	void IdleState::EnterState(ECM::Entity* t_owner)
	{
		std::cout << "Waiting for turn.\n";
		// Set IsInTransition to false
		m_SM->SetInTransition(false);
	}

	void IdleState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		if (m_SM->IsInTransition())
			m_SM->ChangeState("ChooseTarget");
	}

	void ChooseTargetState::EnterState(ECM::Entity* t_owner)
	{
		m_canChoose = true;
		m_chooseFinished = false;
	}

	void ChooseTargetState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		// use t_owner->className() for heuristics
		if (m_canChoose && !m_chooseFinished)
		{
			m_canChoose = false;
				
		}
	}
	
	void StepInState::EnterState(ECM::Entity* t_owner)
	{
		std::cout << "Stepping in.\n";
		m_canStepIn = true;
	}

	void StepInState::Execute(ECM::Entity* t_owner, float t_deltaTime)
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

	void NearTargetState::EnterState(ECM::Entity* t_owner)
	{
		
	}

	void NearTargetState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{

	}

	void ExecSkillState::EnterState(ECM::Entity* t_owner)
	{
		std::cout << "Attacking.\n";
		m_isAttacking = true;
	}

	void ExecSkillState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		
	}

	void StepBackState::EnterState(ECM::Entity* t_owner)
	{
		std::cout << "Stepping back.\n";
		m_canStepBack = true;
	}

	void StepBackState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		
	}

	void ReturnedState::EnterState(ECM::Entity* t_owner)
	{

	}

	void ReturnedState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{

	}

	void FinishState::EnterState(ECM::Entity* t_owner)
	{
		
	}

	void FinishState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{

	}

} }