#ifndef GAME_H
#define GAME_H

#include "DEFINITIONS.hpp"
#include <Engine/Engine.hpp>

#include <memory>
#include <string>

#include <vector>

namespace HJ {

	using namespace Engine;

	class GameManager
	{
		public:
			// stores the amount of gold gathered
			unsigned int gold;
			// stores the unlocked encounters -> helps manage which heroes to use in a battle
			// because every hero is related to the particular encounter
			std::vector<std::string> unlockedEncounters;
	};

	struct GameData 
	{
		SM::StateMachine machine;
		Input::InputManager input;
		Asset::AssetManager assets;
		ECM::EntityManager ents;
		GameManager gm;
	};

	using GameDataRef = std::shared_ptr<GameData>;

	class Game final
	{
		private:
			const float m_deltaTime;
			sf::Clock m_clock;
			GameDataRef m_data;

			void Run();

		public:
			Game(unsigned int t_width, unsigned int t_height, const std::string& t_title);
			~Game() = default;
	};

}

#endif !GAME_H