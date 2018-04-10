#ifndef FROST_GOLEM_AI_STATES
#define FROST_GOLEM_AI_STATES

#include "../Components/StateMachineComponent.hpp"
#include "../Entities/Hero.hpp"
#include "../Damage.hpp"

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
			StepInState() = default;
			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;

		private:
			bool m_canStepIn;
			bool m_canCheck;
			int m_direction;
	};

	class ExecSkillState final : public State
	{
		public:
			ExecSkillState() = default;

			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;

		private:
			bool m_isExecuting;
	};

	class StepBackState final : public State
	{
		public:
			StepBackState() = default;
			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override;

		private:
			bool m_canStepBack;
			bool m_canCheck;
			int m_direction;
	};

	class FinishState final : public State
	{
		public:
			FinishState() = default;
			void EnterState(ECM::Entity* t_owner) override;
			void Execute(ECM::Entity* t_owner, float t_deltaTime) override {}
	};

} }

#endif // !FROST_GOLEM_AI_STATES