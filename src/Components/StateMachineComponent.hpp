#ifndef STATE_MACHINE_COMPONENT
#define STATE_MACHINE_COMPONENT

#include <Engine/ECM/ECM.hpp>
#include <unordered_map>
#include <string>

namespace HJ { namespace Components {

	using namespace Engine;

	class State
	{
		public:
			virtual ~State() = default;
			virtual void EnterState(ECM::Entity*) = 0;
			virtual void Execute(ECM::Entity*, float) = 0;
	};

	class StateMachineComponent : public ECM::Component
	{
		private:
			std::unordered_map<std::string, std::shared_ptr<State>> m_states;
			std::shared_ptr<State> m_currentState;
			std::string m_currentStateName = "";

		public:
			explicit StateMachineComponent(ECM::Entity* t_parent);
			StateMachineComponent() = delete;

			void Update(float t_deltaTime) override;
			void Render() override {}

			void AddState(const std::string& t_name, std::shared_ptr<State> t_state);
			std::shared_ptr<State> GetState(const std::string& t_name) const;
			void RemoveState(const std::string& t_name);
			void ChangeState(const std::string& t_name);
			inline const std::string& currentState() const { return m_currentStateName; }
	};

} }

#endif // !STATE_MACHINE_COMPONENT