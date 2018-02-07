#ifndef MAINMENU_H
#define MAINMENU_H

#include <Engine/Engine.hpp>
#include "../Game.hpp"

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

	private:
		GameDataRef m_data;
		sf::Clock m_clock;

		sf::Text m_titleText;
	};
}

#endif // !MAINMENU_H