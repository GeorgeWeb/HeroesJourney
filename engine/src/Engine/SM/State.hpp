#ifndef SCENE_H
#define SCENE_H

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

			// non-virtual for the moment
			void Pause();
			void Resume();

			void ResizeSceneView(unsigned int t_width, unsigned int t_height);

			sf::View GetSceneView();

		protected:
			virtual void AddEntity(const std::string& t_name, std::shared_ptr<ECM::Entity> t_entity);

		protected:
			// Declare local entities map container
			std::map<std::string, std::shared_ptr<ECM::Entity>> m_entities;
			sf::View m_view;
	};

} }

#endif // !SCENE_H