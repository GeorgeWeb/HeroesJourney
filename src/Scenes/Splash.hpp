#ifndef SPLASH_H
#define SPLASH_H

#include <Engine/Engine.hpp>
#include "../Game.hpp"

namespace HJ {

	using namespace Engine;

	class SplashScene final : public SM::State
	{
		public:
			SplashScene(GameDataRef t_data);

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

#endif // !SPLASH_H
