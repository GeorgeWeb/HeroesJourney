#ifndef STATE_H
#define STATE_H

#include <Engine/ECM/ECM.hpp>
#include <string>

namespace HJ { namespace States {

	using namespace Engine;

	class State
	{
		public:
			virtual ~State() = default;
			virtual void EnterState(ECM::Entity* t_owner) = 0;
			virtual void Execute(ECM::Entity* t_owner, float t_deltaTime) = 0;
	};

} }

#endif !STATE