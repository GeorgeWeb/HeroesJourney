#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.hpp"

#include <memory>
#include <stack>

namespace Engine { namespace SM {

	using StateRef = std::unique_ptr<State>;

	class StateMachine
	{
		public:
			StateMachine() = default;
			~StateMachine() = default;

			void AddState(StateRef t_state, bool t_replacing = true);
			void RemoveState();

			void ProcessStateChanges();

			StateRef& GetActiveState();

		private:
			std::stack<StateRef> m_states;
			StateRef m_newState;

			bool m_isRemoving = false;
			bool m_isAdding = false;
			bool m_isReplacing = false;
	};

} }
#endif // !STATE_MACHINE_H
