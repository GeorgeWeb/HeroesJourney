#ifndef MAINMENU_H
#define MAINMENU_H

#include <Engine/Engine.hpp>
#include "../Game.hpp"

#include <Engine/ECM/Components/SpriteComponent.hpp>

namespace HJ {

	using namespace Engine;

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
	};
}

#endif // !MAINMENU_H
