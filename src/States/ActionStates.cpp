#include "ActionStates.hpp"

#include <iostream>

namespace HJ { namespace States {
	
	void IdleState::EnterState(ECM::Entity* t_owner)
	{
		std::cout << "Waiting for turn.\n";
		m_SM->SetInTransition(false);
	}

	void IdleState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		if (m_SM->IsInTransition())
			m_SM->ChangeState("ChooseTarget");
	}

	void ChooseTargetState::EnterState(ECM::Entity* t_owner)
	{
		std::cout << m_SM->GetInitiator()->className() << std::endl;
		m_canChoose = true;
		m_heuristicEval->SetComplete(false);
		std::cout << "Choosing target.\n";
	}

	void ChooseTargetState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{	
		if (m_canChoose && !m_heuristicEval->IsComplete())
		{
			std::cout << "Evaluating\n";
			m_canChoose = false;
			m_heuristicEval->Initialize(m_SM->GetInitiator(), m_SM->GetTargets(), m_SM->GetUsedSkill());
			m_heuristicEval->Evaluate();

		}
		else if (!m_canChoose && m_heuristicEval->IsComplete())
		{
			if (m_heuristicEval->GetUsedSkill()->dmgBase == DAMAGE_BASE::MELEE)
			{
				m_canChoose = false;
				m_heuristicEval->SetComplete(false);
				m_SM->ChangeState("StepIn");
			}
			else
			{
				m_canChoose = false;
				m_heuristicEval->SetComplete(false);
				m_SM->ChangeState("ExecSkill");
			}
		}
	}
	
	void StepInState::EnterState(ECM::Entity* t_owner)
	{
		std::cout << "Stepping in.\n";
		std::cout << m_SM->endPos.x;
		m_canStepIn = true;
		m_canCheck = false;
		m_direction = (m_SM->endPos.x - m_SM->GetInitiator()->GetPosition().x > 0) ? 1 : -1;
	}

	void StepInState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		if (m_canStepIn && !m_canCheck)
		{
			m_SM->GetInitiator()->Move(sf::Vector2f(m_SM->speed * m_direction, 0.0f));
			m_canStepIn = false;
			m_canCheck = true;
		}
		else if (!m_canStepIn && m_canCheck)
		{
			float predictedPos = m_SM->GetInitiator()->GetPosition().x + (m_SM->speed * m_direction);
			if (predictedPos * m_direction <= m_SM->endPos.x * m_direction)
			{
				m_canStepIn = true;
				m_canCheck = false;
			}
			else
			{
				m_canStepIn = false;
				m_canCheck = false;
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
		std::cout << "Targets size: " << m_heuristicEval->GetTargets().size() << std::endl;
		// IF BOSS DOESN"T HAVE A BASIC ATTACK
		if (m_heuristicEval->GetUsedSkill() == nullptr)
		{
			m_isExecuting = false;
			m_SM->ChangeState("StepBack");
		}

		// Create the damage
		Damage damage(m_heuristicEval->GetInitiator(), m_heuristicEval->GetUsedSkill(), m_SM->random.NextInt(100, 1));
		// Send the damage
		if (m_isExecuting)
		{
			m_isExecuting = false;
			for (auto& hero : m_heuristicEval->GetTargets())
			{
				auto dmg = damage.SendDamage(hero);
				std::cout << "\n\nDealt: " << dmg << "to " << hero->className() << "!! WOOHOOO !!\n";
				std::cout << "HP left: " << hero->GetHealth() << "to " << "!! EEMI TOLKOZ !!\n\n";
			}
			
			if(m_heuristicEval->GetUsedSkill()->dmgBase == DAMAGE_BASE::MELEE)
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
		m_direction = (m_SM->endPos.x - m_SM->GetInitiator()->GetPosition().x > 0) ? 1 : -1;
	}

	void StepBackState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
		if (m_canStepBack && !m_canCheck)
		{
			m_SM->GetInitiator()->Move(sf::Vector2f(m_SM->speed * m_direction, 0.0f));
			m_canStepBack = false;
			m_canCheck = true;
		}
		else if (!m_canStepBack && m_canCheck)
		{
			float predictedPos = m_SM->GetInitiator()->GetPosition().x + (m_SM->speed * m_direction);
			if (predictedPos * m_direction <= m_SM->endPos.x * m_direction)
			{
				m_canStepBack = true;
				m_canCheck = false;
			}
			else
			{
				m_canStepBack = false;
				m_canCheck = false;
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