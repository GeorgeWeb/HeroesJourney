#ifndef FROST_GOLEM_AI_STATES
#define FROST_GOLEM_AI_STATES

#include "../Components/StateMachineComponent.hpp"
#include "../Entities/Hero.hpp"

#include <vector>

namespace HJ { namespace States {

	using namespace Engine;
	
	class IdleState final : public State
	{
		public:
			IdleState() = default;
			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;
	};

	class ChooseTargetState final : public State
	{
		public:
			ChooseTargetState() = default;
			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;

		private:
			bool m_canChoose;
			bool m_chooseFinished;
	};

	class StepInState final : public State
	{
		public:
			StepInState() : m_canStepIn(false) {}
			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;

		private:
			sf::Vector2f m_position;
			float m_speed;
			bool m_canStepIn;
	};

	class NearTargetState final : public State
	{
		public:
			NearTargetState() = default;
			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;
	};

	class ExecSkillState final : public State
	{
		public:
			ExecSkillState() : m_isAttacking(false) {}

			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;

		private:
			bool m_isAttacking;
	};

	class StepBackState final : public State
	{
		public:
			StepBackState() : m_canStepBack(false) {}
			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;

		private:
			bool m_canStepBack;
	};

	class ReturnedState final : public State
	{
	public:
		ReturnedState() = default;
		void EnterState(ECM::Entity* t_owner) override;
		void Execute(ECM::Entity* t_owner, float t_deltaTime) override;
	};

	class FinishState final : public State
	{
		public:
			FinishState() = default;
			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;
	};

} }

#endif // !FROST_GOLEM_AI_STATES