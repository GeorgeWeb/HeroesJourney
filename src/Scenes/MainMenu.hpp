#ifndef MAINMENU_H
#define MAINMENU_H

#include <Engine/Engine.hpp>
#include "../Game.hpp"
#include <Engine/GUI/GUIElement.hpp>

namespace HJ {

	class MainMenuScene final : public SM::State
	{
		public:
			MainMenuScene(GameDataRef t_data);

			void Init() override final;

			void HandleInput() override final;
			void Update(float t_delatTime) override final;
			void Draw(float t_deltaTime) override final;

		private:
			GameDataRef m_data;
			sf::Clock m_clock;
			
			sf::Sprite m_background;
			std::shared_ptr<GUI::GUIElement> m_startBtn;
			std::shared_ptr<GUI::GUIElement> m_quitBtn;
			
			sf::Text m_titleText;
	};
}

#endif // !MAINMENU_H
