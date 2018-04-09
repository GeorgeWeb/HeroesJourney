#include "ActionResolver.hpp"

namespace HJ { namespace Entities {

	void ActionResolver::Activate(std::shared_ptr<Entities::Hero> t_initiator, std::vector<std::shared_ptr<Entities::Hero>> t_targets, 
		std::shared_ptr<Skill> t_usedSkill)
	{
		// initialize the actors (senders/receivers)
		m_smComp->SetInitiator(t_initiator);
		m_smComp->SetTargets(t_targets);
		m_smComp->SetUsedSkill(t_usedSkill);

		// initialize the states
		// TODO: ...
		
		// run the state machine
		m_smComp->SetInTransition(true);
	}

	void ActionResolver::Stop()
	{
		m_smComp->ChangeState("Idle");
		m_active = false;
	}

} }
