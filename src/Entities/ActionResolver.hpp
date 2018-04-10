#ifndef ACTION_RESOLVER_H
#define ACTION_RESOLVER_H

#include "../States/ActionStates.hpp"

namespace HJ { namespace Entities {

	class ActionResolver final : public Engine::ECM::Entity
	{
		private:
			std::shared_ptr<Components::StateMachineComponent> m_smComp;
			std::shared_ptr<Components::HeuristicEvalComponent> m_heuristicEvalComp;
			bool m_active;

		public:
			ActionResolver();
			~ActionResolver() = default;

			ActionResolver* GetType() override final { return this; }

			inline bool const IsActive() const { return m_active; }
			// (re-)initialize the StateMachineComponent data on action resolve call
			void Activate(std::shared_ptr<Entities::Hero> t_initiator, std::vector<std::shared_ptr<Entities::Hero>> t_targets,
				// if a skill is being used:
				std::shared_ptr<Skill> t_usedSkill = nullptr);

			// reset StateMachine to initial
			void Stop();

			std::shared_ptr<Components::StateMachineComponent> GetSMComponent();
	};

} }

#endif // !ACTION_RESOLVER_H
