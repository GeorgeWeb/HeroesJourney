#ifndef STATE_H
#define STATE_H

#include <Engine/ECM/ECM.hpp>
#include <string>

namespace HJ { 
	
	// Forward declare StateMachineComponent
	namespace Components 
	{
		class StateMachineComponent;
	}
	
	namespace States {

	class State
	{
		public:
			virtual ~State() = default;
			virtual void EnterState(Engine::ECM::Entity* t_owner) = 0;
			virtual void Execute(Engine::ECM::Entity* t_owner, float t_deltaTime) = 0;

			inline void InitSM(Components::StateMachineComponent* t_SM) { m_SM = t_SM; }

		protected:
			Components::StateMachineComponent* m_SM;
			// create pointer to heuristics component & Link
	};

} }

#endif !STATE