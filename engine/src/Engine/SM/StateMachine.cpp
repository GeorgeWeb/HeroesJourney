#include "StateMachine.hpp"

namespace Engine { namespace SM {

	void StateMachine::AddState(StateRef t_state, bool t_replacing)
	{
		m_isAdding = true;
		m_isReplacing = t_replacing;
		m_newState = std::move(t_state); ///> moving the ownership of the state to a new one
	}

	void StateMachine::RemoveState()
	{
		m_isRemoving = true;
	}

	void StateMachine::ProcessStateChanges()
	{
		if (m_isRemoving && !m_states.empty())
		{
			m_states.pop();
			
			if (!m_states.empty())
				m_states.top()->Resume();

			m_isRemoving = false;
		}

		if (m_isAdding)
		{
			if (!m_states.empty())
			{
				if (m_isReplacing)
					m_states.pop();
				else
					m_states.top()->Pause();
			}

			m_states.push(std::move(m_newState));
			m_states.top()->Init();
			m_isAdding = false;
		}
	}

	StateRef& StateMachine::GetActiveState()
	{
		return m_states.top();
	}

} }