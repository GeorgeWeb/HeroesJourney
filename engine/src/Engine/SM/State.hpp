#ifndef STATE_H
#define STATE_H

#include "../Entity/Entity.hpp"

#include <map>
#include <memory>

namespace Engine { namespace SM {

	class State
	{
		public:
			virtual ~State() = default;

			// mandatory for managing the state
			virtual void Init() = 0;
			virtual void HandleInput() = 0;
			virtual void Update(float t_deltaTime) = 0;
			virtual void Draw(float t_deltaTime) = 0;

			// Not neccessary, but useful
			virtual void Pause() {}
			virtual void Resume() {}

		protected:
			virtual void AddEntity(const std::string& t_name, std::shared_ptr<Entity::Entity> t_entity);

		protected:
			std::map<std::string, std::shared_ptr<Entity::Entity>> m_entities;
	};

} }

#endif // !STATE_H