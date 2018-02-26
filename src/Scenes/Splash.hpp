#ifndef SPLASH_H
#define SPLASH_H

#include <Engine/Engine.hpp>
#include "../Game.hpp"

#include "../Entities/Knight.hpp"
#include "../Entities/AnimatedLogo.hpp"

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

		protected:
			void AddEntity(const std::string& t_name, std::shared_ptr<ECM::Entity> t_entity) override final;

		private:
			GameDataRef m_data;
			bool m_shouldFade = false;
			
			// temp
			sf::Color bgColor;
			sf::Text m_titleText;

			// Entities
			std::shared_ptr<Entities::AnimatedLogo> m_logo;
	};
}

#endif // !SPLASH_H