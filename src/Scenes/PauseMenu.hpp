#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include <Engine/Engine.hpp>
#include "../Game.hpp"

#include <Engine/ECM/EntityManager.hpp>

namespace HJ {

	using namespace Engine;

	class PauseMenuScene final : public SM::State
	{
		public:
			PauseMenuScene(GameDataRef t_data);

			void Init() override final;

			void HandleInput() override final;
			void Update(float t_delatTime) override final;
			void Draw(float t_deltaTime) override final;

		protected:
			void AddEntity(const std::string& t_name, std::shared_ptr<ECM::Entity> t_entity) override final;

		private:
			GameDataRef m_data;
			sf::Clock m_clock;
			bool m_renderCheck = true;
	};
}

#endif // !PAUSE_MENU_H