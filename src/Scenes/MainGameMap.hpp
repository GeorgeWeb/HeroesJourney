#ifndef MAIN_GAME_MAP_H
#define MAIN_GAME_MAP_H

#include <Engine/Engine.hpp>
#include "../Game.hpp"

namespace HeroesJourney {

	using namespace Engine;

	class MainGameMapScene final : public SM::State
	{
	public:
		MainGameMapScene(GameDataRef t_data);

		void Init() override final;

		void HandleInput() override final;
		void Update(float t_delatTime) override final;
		void Draw(float t_deltaTime) override final;

	private:
		GameDataRef m_data;
		sf::Clock m_clock;

		sf::Sprite m_background;
	};
}

#endif // !MAIN_GAME_MAP_H
