#ifndef STATE_MACHINE_COMPONENT
#define STATE_MACHINE_COMPONENT

#include "../States/State.hpp"
#include <unordered_map>
#include "../Entities/Hero.hpp"

#include <Engine/Utils/Random.hpp>


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

		// [hero/ai] specific
		private:
			std::vector<std::shared_ptr<Entities::Hero>> m_targets = {};
			std::shared_ptr<Entities::Hero> m_initiator = nullptr;
			std::shared_ptr<Skill> m_usedSkill = nullptr;

		public:
			inline std::vector<std::shared_ptr<Entities::Hero>> GetTargets() { return m_targets; }
			inline std::shared_ptr<Entities::Hero> GetInitiator() { return m_initiator; }
			inline std::shared_ptr<Skill> GetUsedSkill() { return m_usedSkill; }
			
			inline void SetTargets(std::vector<std::shared_ptr<Entities::Hero>> t_targets) { m_targets = t_targets; }
			inline void SetInitiator(std::shared_ptr<Entities::Hero> t_initiator) { m_initiator = t_initiator; }
			inline void SetUsedSkill(std::shared_ptr<Skill> t_usedSkill) { m_usedSkill = t_usedSkill; }

			inline void AutoSetPosition(const sf::Vector2f& t_position);

			// ...
			sf::Vector2f initPos;
			sf::Vector2f endPos;
			float speed = 10.0f;

			Engine::Utils::Random random;
	};

} }

#endif // !STATE_MACHINE_COMPONENT