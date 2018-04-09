#ifndef STATE_MACHINE_COMPONENT
#define STATE_MACHINE_COMPONENT

#include "../States/State.hpp"
#include <unordered_map>

namespace HJ { namespace Components {

	using namespace Engine;

	class StateMachineComponent final : public ECM::Component
	{
		public:
			StateMachineComponent() = delete;
			explicit StateMachineComponent(ECM::Entity* t_parent);

			void Update(float t_deltaTime) override;
			void Render() override {}

			void AddState(const std::string& t_name, std::shared_ptr<States::State> t_state);
			std::shared_ptr<States::State> GetState(const std::string& t_name) const;
			void RemoveState(const std::string& t_name);
			void ChangeState(const std::string& t_name);
			inline const std::string& CurrentState() const { return m_currentStateName; }

			inline bool IsInTransition() const { return m_isInTransition; }
			inline void SetInTransition(bool t_isInTransition) { m_isInTransition = t_isInTransition; }

		private:
			std::unordered_map<std::string, std::shared_ptr<States::State>> m_states;
			std::shared_ptr<States::State> m_currentState;
			std::string m_currentStateName = "";
			bool m_isInTransition;
	};

} }

#endif // !STATE_MACHINE_COMPONENT