#ifndef SETTINGS_SCENE_H
#define SETTINGS_SCENE_H

#include "../Game.hpp"
#include <Engine/Engine.hpp>
#include <Engine/System/Settings.hpp>

#include "../Entities/Button.hpp"
#include <map>

namespace HJ {

	using namespace Engine;

	class SettingsScene final : public SM::State
	{
		public:
			SettingsScene(GameDataRef t_data);

			void Init() override final;

			void HandleInput() override final;
			void Update(float t_deltaTime) override final;
			void UpdateSettings();
			void Draw(float t_deltaTime) override final;

		protected:
			void AddEntity(const std::string& t_name, std::shared_ptr<ECM::Entity> t_entity) override final;

		private:
			GameDataRef m_data;

			std::shared_ptr<Entities::Button> m_changeBackBtn;
			std::shared_ptr<Entities::Button> m_changePauseBtn;
			std::shared_ptr<Entities::Button> m_changeSkipBtn;

			std::map<std::string, std::shared_ptr<Entities::Button>> m_controls;
	};
}








#endif // !SETTINGS_SCENE_H
