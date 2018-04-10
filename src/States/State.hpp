#ifndef STATE_H
#define STATE_H

#include <Engine/ECM/ECM.hpp>
#include <string>

namespace HJ { 
	
	// Forward declarations to be used as members in each State
	namespace Components 
	{
		class StateMachineComponent;
		class HeuristicEvalComponent;
	}
	
	namespace States {

	class State
	{
		public:
			virtual ~State() = default;
			virtual void EnterState(Engine::ECM::Entity* t_owner) = 0;
			virtual void Execute(Engine::ECM::Entity* t_owner, float t_deltaTime) = 0;

			inline void InitSM(Components::StateMachineComponent* t_SM) { m_SM = t_SM; }
			inline void InitHeuristic(Components::HeuristicEvalComponent* t_heuristic) { m_heuristicEval = t_heuristic; }

		protected:
			Components::StateMachineComponent* m_SM;
			Components::HeuristicEvalComponent* m_heuristicEval;
	};

} }

#endif !STATE