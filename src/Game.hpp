#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include <vector>
#include <utility>

#include "DEFINITIONS.hpp"
#include <Engine/Engine.hpp>
#include "Entities/Knight.hpp"
#include "Entities/Bard.hpp"
#include "Entities/Sorceress.hpp"
#include "Entities/Rogue.hpp"
#include "Entities/EvilFrostMage.hpp"

namespace HJ {

	using namespace Engine;

	class GameManager
	{
		public:
			// amount of gold gathered
			unsigned int gold = 100;
			
			// amount of potions acquired/bought
			unsigned int healthPot = 1;
			unsigned int manaPot = 1;
			
			// unlocked encounters + the number of times each one is completed.
			// this helps manage which heroes are available for the battle,
			// because every hero is related to a particular encounter
			std::vector<std::pair<std::string, unsigned int>> unlockedEncounters;
			
			// good/heroes characters
			std::shared_ptr<Entities::Knight> hKnight;
			std::shared_ptr<Entities::Bard> hBard;
			std::shared_ptr<Entities::Sorceress> hSorceress;
			std::shared_ptr<Entities::Rogue> hRogue;

			// evil/enemies characters
			std::shared_ptr<Entities::EvilFrostMage> eFrostMage;
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