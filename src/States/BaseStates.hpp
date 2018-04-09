#ifndef FROST_GOLEM_AI_STATES
#define FROST_GOLEM_AI_STATES

#include "../Components/StateMachineComponent.hpp"
#include "../Entities/Hero.hpp"

#include <vector>

namespace HJ { namespace States {

	using namespace Engine;
	
	class BaseIdleState final : public State
	{
		public:
			BaseIdleState() = default;
			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;
	};

	class BaseChooseTargetState final : public State
	{
		public:
			BaseChooseTargetState() = default;
			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;

		private:
			bool m_canChoose;
			bool m_chooseFinished;
	};

	class BaseStepInState final : public State
	{
		public:
			BaseStepInState(sf::Vector2f t_position, float t_speed)
				: m_position(t_position), m_speed(t_speed), m_canStepIn(false) {}
			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;

		private:
			sf::Vector2f m_position;
			float m_speed;
			bool m_canStepIn;
	};

	class BaseNearTargetState final : public State
	{
		public:
			BaseNearTargetState() = default;
			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;
	};

	class BaseAttackState final : public State
	{
		public:
			BaseAttackState(std::vector<std::shared_ptr<Entities::Hero>> t_heroes, unsigned int t_damage)
				: m_heroes(t_heroes), m_damage(t_damage), m_isAttacking(false) {}

			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;

		private:
			std::vector<std::shared_ptr<Entities::Hero>> m_heroes;
			unsigned int m_damage;
			bool m_isAttacking;
	};

	class BaseStepBackState final : public State
	{
		public:
			BaseStepBackState(sf::Vector2f t_position, float t_speed)
				: m_position(t_position), m_speed(t_speed), m_canStepBack(false) {}
			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;

		private:
			sf::Vector2f m_position;
			float m_speed;
			bool m_canStepBack;
	};

	class BaseFinishState final : public State
	{
		public:
			BaseFinishState() = default;
			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;
	};

} }

#endif // !FROST_GOLEM_AI_STATES