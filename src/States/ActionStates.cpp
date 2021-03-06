#include "ActionStates.hpp"
#include <iostream>

namespace HJ { namespace States {
	
	void IdleState::EnterState(ECM::Entity* t_owner)
	{
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
		m_heuristicEval->SetComplete(false);
	}

	void ChooseTargetState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{	
		if (m_canChoose && !m_heuristicEval->IsComplete())
		{
			m_canChoose = false;
			m_heuristicEval->Initialize(m_SM->GetInitiator(), m_SM->GetTargets(), m_SM->GetUsedSkill());
			m_heuristicEval->Evaluate();

		}
		else if (!m_canChoose && m_heuristicEval->IsComplete())
		{
			if (m_heuristicEval->GetUsedSkill()->dmgBase == DAMAGE_BASE::DEFENCE)
			{
				m_canChoose = false;
				m_heuristicEval->SetComplete(false);
				m_SM->ChangeState("ExecSkill");
			}
			else
			{
				m_canChoose = false;
				m_heuristicEval->SetComplete(false);
				m_SM->ChangeState("StepIn");
			}
		}
	}
	
	void StepInState::EnterState(ECM::Entity* t_owner)
	{
		m_canStepIn = true;
		m_canCheck = false;
		if (m_heuristicEval->GetUsedSkill()->dmgBase != DAMAGE_BASE::MELEE)
		{
			if (m_SM->GetInitiator()->className() == "Rogue")
			{
				m_SM->endPos.x = (m_SM->endPos.x - m_SM->GetInitiator()->GetPosition().x > 0) ? m_SM->endPos.x / 2.0f : m_SM->endPos.x * 2.5f;
				m_SM->speed *= 0.5f;
			}
			else
			{
				m_SM->endPos.x = (m_SM->endPos.x - m_SM->GetInitiator()->GetPosition().x > 0) ? m_SM->endPos.x / 3.0f : m_SM->endPos.x * 2.5f;
				m_SM->speed *= 0.5f;
			}
		}
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
		m_isExecuting = true;
	}

	void ExecSkillState::Execute(ECM::Entity* t_owner, float t_deltaTime)
	{
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

			// play skill sounds
			if (!m_heuristicEval->GetUsedSkill()->soundRefName.empty() && m_heuristicEval->GetInitiator()->heroType() == Entities::HERO_TYPE::GOOD)
			{
				m_skillBfr = m_assets.LoadBuffer(m_heuristicEval->GetUsedSkill()->soundRefName);
				m_skillSnd.setBuffer(*m_skillBfr);
				m_skillSnd.play();
			}

			for (auto& hero : m_heuristicEval->GetTargets())
			{
				auto dmg = damage.SendDamage(hero);
				if (dmg == "DODGED") m_dodgeCount++;
			}

			// play sound on dodge
			if (m_dodgeCount > 0)
			{
				m_dodgeBfr = m_assets.LoadBuffer(m_heuristicEval->GetUsedSkill()->soundRefName);
				m_dodgeSnd.setBuffer(*m_dodgeBfr);
				m_dodgeSnd.play();
				m_dodgeCount = 0;
			}
			
			if(m_heuristicEval->GetUsedSkill()->dmgBase == DAMAGE_BASE::DEFENCE)
				m_SM->ChangeState("Finish");
			else
				m_SM->ChangeState("StepBack");
		}
	}

	void StepBackState::EnterState(ECM::Entity* t_owner)
	{
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

} }