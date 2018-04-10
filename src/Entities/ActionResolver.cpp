#include "ActionResolver.hpp"
#include "../DEFINITIONS.hpp"

namespace HJ { namespace Entities {

	ActionResolver::ActionResolver() :
		m_smComp(AddComponent<Components::StateMachineComponent>("C_ActionStateMachine")),
		m_heuristicEvalComp(AddComponent<Components::HeuristicEvalComponent>("C_HeuristicEval")),
		m_active(false)
	{
		// initialize the states
		m_smComp->AddState("Idle", std::make_shared<States::IdleState>());
		m_smComp->GetState("Idle")->InitHeuristic(this->GetHEvalComponent().get());
		
		m_smComp->AddState("ChooseTarget", std::make_shared<States::ChooseTargetState>());
		m_smComp->GetState("ChooseTarget")->InitHeuristic(this->GetHEvalComponent().get());
		
		m_smComp->AddState("StepIn", std::make_shared<States::StepInState>());
		m_smComp->GetState("StepIn")->InitHeuristic(this->GetHEvalComponent().get());
		
		m_smComp->AddState("ExecSkill", std::make_shared<States::ExecSkillState>());
		m_smComp->GetState("ExecSkill")->InitHeuristic(this->GetHEvalComponent().get());
		
		m_smComp->AddState("StepBack", std::make_shared<States::StepBackState>());
		m_smComp->GetState("StepBack")->InitHeuristic(this->GetHEvalComponent().get());
		
		m_smComp->AddState("Finish", std::make_shared<States::FinishState>());
		m_smComp->GetState("Finish")->InitHeuristic(this->GetHEvalComponent().get());
		
		m_smComp->ChangeState("Idle");
	}

	void ActionResolver::Init()
	{
		SetVisible(false);
		SetAlive(true);
	}

	void ActionResolver::Update(float t_deltaTime)
	{
		Engine::ECM::Entity::Update(t_deltaTime);
	}

	void ActionResolver::Render()
	{
		Engine::ECM::Entity::Render();
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
		m_smComp->speed = 25.0f;
		// run the state machine
		m_smComp->SetInTransition(true);
		// activate>
		m_active = true;
	}

	void ActionResolver::Stop()
	{
		m_smComp->ChangeState("Idle");
		m_active = false;
	}

	std::shared_ptr<Components::StateMachineComponent> ActionResolver::GetSMComponent()
	{
		return m_smComp;
	}

	std::shared_ptr<Components::HeuristicEvalComponent> ActionResolver::GetHEvalComponent()
	{
		return m_heuristicEvalComp;
	}

} }
