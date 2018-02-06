#ifndef GAME_H
#define GAME_H

#include "DEFINITIONS.hpp"
#include <Engine/Engine.hpp>

#include <memory>
#include <string>

namespace HJ {

	using namespace Engine;

	struct GameData 
	{
		SM::StateMachine machine;
		Asset::AssetManager assets;
		Input::InputManager input;
		// only used for storing/retrieving shared (between scenes) entities
		Entity::EntityManager gameObj = Entity::EntityManager::getInstance();
	};

	using GameDataRef = std::shared_ptr<GameData>;

	class Game final
	{
		private:
			const float m_deltaTime = 1.0f / 60.0f;
			sf::Clock m_clock;
			GameDataRef m_data = std::make_shared<GameData>();

			void Run();

		public:
			Game(unsigned int t_width, unsigned int t_height, const std::string& t_title);
			~Game() = default;
	};

}

#endif !GAME_H