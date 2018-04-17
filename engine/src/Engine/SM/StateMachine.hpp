#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "State.hpp"

#include <memory>
#include <stack>

namespace Engine { namespace SM {

	using StateRef = std::shared_ptr<State>;

	class StateMachine final
	{
		public:
			StateMachine() = default;
			~StateMachine();

			void AddState(StateRef t_state, bool t_replacing = true);
			void RemoveState();

			void ProcessStateChanges();

			inline StateRef& GetActiveState() { return m_states.top(); }

		private:
			std::stack<StateRef> m_states;
			StateRef m_newState;

			bool m_isRemoving = false;
			bool m_isAdding = false;
			bool m_isReplacing = false;
	};

} }
#endif // !SCENE_MANAGER_H
