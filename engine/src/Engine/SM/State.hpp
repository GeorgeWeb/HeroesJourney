#ifndef STATE_H
#define STATE_H

#include "../ECM/ECM.hpp"

#include <memory>
#include <map>

namespace Engine { namespace SM {

	class State
	{
		public:
			virtual ~State() = default;

			// mandatory for managing the state
			virtual void Init() = 0;
			virtual void HandleInput() = 0;
			virtual void Draw(float t_deltaTime) = 0;

			virtual void Update(float t_deltaTime) = 0;

			// Not neccessary, but useful
			virtual void Pause();
			virtual void Resume();

			// TODO:
			// Add entities map
	};

} }

#endif // !STATE_H