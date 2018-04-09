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
		// auto heuristicEval = t_owner->GetComponent<HeuristicEvalComponent>("HeuristicEval");
		// heuristicEval->SetComplete(false);
	}

	void ChooseTargetState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		// auto heuristicEval = t_owner->GetComponent<HeuristicEvalComponent>("HeuristicEval");
		// use t_owner->className() for heuristics
		/*
		if (m_canChoose && !heuristicEval->IsComplete())
		{
			m_canChoose = false;
			heuristicEval->SetData(..., ..., ...);
			heuristicEval->Evaluate();
		}
		else if (!m_canChoose && heuristicEval->IsComplete())
		{
			m_SM->SetUsedSkill(heuristicEval->GetSkill());
			m_SM->SetTargets(heuristicEval->GetTargets());

			if (m_SM->GetUsedSkill()->dmgBase == DAMAGE_BASE::MELEE)
			{
				// heuristicEval->SetComplete(false);
				m_SM->AutoSetPos();
				m_SM->ChangeState("StepIn");
			}
			else
			{
				// heuristicEval->SetComplete(false);
				m_SM->ChangeState("ExecSkill");
			}
		}
		*/
	}
	
	void StepInState::EnterState(ECM::Entity* t_owner)
	{
		std::cout << "Stepping in.\n";
		m_canStepIn = true;
		m_canCheck = false;
		m_direction = (m_SM->endPos.x - t_owner->GetPosition().x > 0) ? 1 : -1;
	}

	void StepInState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		if (m_canStepIn && !m_canCheck)
		{
			t_owner->Move(sf::Vector2f(m_SM->speed * m_direction, 0.0f));
			m_canStepIn = false;
			m_canCheck = true;
		}
		else if (!m_canStepIn && m_canCheck)
		{
			if (t_owner->GetPosition().x * m_direction <= m_SM->endPos.x * m_direction)
			{
				m_canStepIn = false;
				m_canCheck = false;
			}
			else
			{
				m_canStepIn = true;
				m_canCheck = true;
			}
		}
		else if (!m_canStepIn && !m_canCheck) 
		{
			// change state to attack condition
			m_SM->ChangeState("ExecSkill");
		}
	}

	void ExecSkillState::EnterState(ECM::Entity* t_owner)
	{
		std::cout << "Executing skill.\n";
		m_isExecuting = true;
	}

	void ExecSkillState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		// Create the damage
		Damage damage(m_SM->GetInitiator(), m_SM->GetUsedSkill(), m_SM->random.NextInt(100, 0));
		// Send the damage
		if (m_isExecuting)
		{
			m_isExecuting = false;
			for (auto hero : m_SM->GetTargets())
			{
				damage.SendDamage(hero);
			}
			if (m_SM->GetUsedSkill()->dmgBase == DAMAGE_BASE::MELEE)
				m_SM->ChangeState("StepBack");
			else
				m_SM->ChangeState("Finish");
		}
	}

	void StepBackState::EnterState(ECM::Entity* t_owner)
	{
		std::cout << "Stepping back.\n";
		m_canStepBack = true;
		m_canCheck = false;
		m_SM->endPos = m_SM->initPos;
		m_direction = (m_SM->endPos.x - t_owner->GetPosition().x > 0) ? 1 : -1;
	}

	void StepBackState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		if (m_canStepBack && !m_canCheck)
		{
			t_owner->Move(sf::Vector2f(m_SM->speed * m_direction, 0.0f));
			m_canStepBack = false;
			m_canCheck = true;
		}
		else if (!m_canStepBack && m_canCheck)
		{
			if (t_owner->GetPosition().x * m_direction <= m_SM->endPos.x * m_direction)
			{
				m_canStepBack = false;
				m_canCheck = false;
			}
			else
			{
				m_canStepBack = true;
				m_canCheck = true;
			}
		}
		else if (!m_canStepBack && !m_canCheck)
		{
			// change state to attack condition
			m_SM->ChangeState("Finish");
		}
	}

	void FinishState::EnterState(ECM::Entity* t_owner)
	{
		std::cout << "Finished!\n";
	}

} }