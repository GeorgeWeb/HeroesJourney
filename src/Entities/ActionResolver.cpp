#include "ActionResolver.hpp"

namespace HJ { namespace Entities {

	ActionResolver::ActionResolver()
		: m_smComp(AddComponent<Components::StateMachineComponent>("C_ActionStateMachine"))
	{
		// initialize the states
		m_smComp->AddState("Idle", std::make_shared<States::IdleState>());
		m_smComp->AddState("ChooseTarget", std::make_shared<States::ChooseTargetState>());
		m_smComp->AddState("StepIn", std::make_shared<States::StepInState>());
		m_smComp->AddState("ExecSkill", std::make_shared<States::ExecSkillState>());
		m_smComp->AddState("StepBack", std::make_shared<States::StepBackState>());
		m_smComp->AddState("Finish", std::make_shared<States::FinishState>());
	}

	void ActionResolver::Activate(std::shared_ptr<Entities::Hero> t_initiator, std::vector<std::shared_ptr<Entities::Hero>> t_targets,
		std::shared_ptr<Skill> t_usedSkill)
	{
		// initialize the actors (senders/receivers)
		m_smComp->SetInitiator(t_initiator);
		m_smComp->SetTargets(t_targets);
		m_smComp->SetUsedSkill(t_usedSkill);
		// set the initial position of the initiating actor
		m_smComp->initPos = t_initiator->GetPosition();
		m_smComp->speed = 7.5f;
		// run the state machine
		m_smComp->SetInTransition(true);
	}

	void ActionResolver::Stop()
	{
		m_smComp->ChangeState("Idle");
		m_active = false;
	}

	std::shared_ptr<Components::StateMachineComponent> ActionResolver::GetSMComponent()
	{
		return std::shared_ptr<Components::StateMachineComponent>();
	}

} }
