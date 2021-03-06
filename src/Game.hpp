#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include <vector>
#include <utility>

// resources
#include "DEFINITIONS.hpp"
// engine
#include <Engine/Engine.hpp>
// heroes
#include "Entities/Knight.hpp"
#include "Entities/Bard.hpp"
#include "Entities/Sorceress.hpp"
#include "Entities/Rogue.hpp"
// buildings
#include "Entities/Infirmary.hpp"
#include "Entities/Blacksmith.hpp"
#include "Entities/Library.hpp"
#include "Entities/Inn.hpp"
#include "Entities/GeneralStore.hpp"

// game controls
#include "Controls.hpp"

namespace HJ {

	using namespace Engine;

	// [Serializable]
	class GameManager final
	{
		public:
			// amount of gold gathered
			int gold = 10;
			
			// where the outcome leads
			int nextEncounter = 0;
			
			// reward after battle
			int loot = 0;
			
			//
			bool battlePassed = true;
			int trollPassed = 0;
			int cyclopsPassed = 0;
			int harpyPassed = 0;
			int magePassed = 0;

			// amount of potions acquired/bought
			int healthPot = 1;
			int manaPot = 1;

			// resources entities
			std::shared_ptr<ECM::Entity> cHealthPot;
			std::shared_ptr<ECM::Entity> cManaPot;
			std::shared_ptr<ECM::Entity> cGold;

			// good/heroes characters
			std::shared_ptr<Entities::Knight> hKnight;
			std::shared_ptr<Entities::Bard> hBard;
			std::shared_ptr<Entities::Sorceress> hSorceress;
			std::shared_ptr<Entities::Rogue> hRogue;

			// inside-castle buildings
			std::shared_ptr<Entities::Infirmary> infirmary;
			std::shared_ptr<Entities::Blacksmith> blacksmith;
			std::shared_ptr<Entities::Library> library;
			std::shared_ptr<Entities::Inn> inn;
			std::shared_ptr<Entities::GeneralStore> store;
	};

	struct GameData final
	{
		System::Settings settings;
		SM::StateMachine machine;
		Input::InputManager input;
		Asset::AssetManager assets;
		ECM::EntityManager ents;
		Utils::FileIO saveData;
		GameManager gm;
	};

	using GameDataRef = std::shared_ptr<GameData>;

	class Game final
	{
		private:
			const float m_deltaTime;
			sf::Clock m_clock;
			GameDataRef m_data;

		public:
			Game() = delete;
			Game(unsigned int t_width, unsigned int t_height, const std::string& t_title, System::SCREEN_MODE t_mode, bool t_vsync = true);
			~Game() = default;
		
		private:
			// fires up the game :P (LinkStart ref.: SwordArtsOnline)
			void GameLoop();
	};

	enum class BATTLE_TURN : int
	{
		HERO = 0,
		EVIL = 1,
		BETWEEN = 2
	};

	enum class BATTLE_STATUS : int
	{
		PLAYING = 0,
		WON     = 1,
		LOST    = 2
	};

}

#endif !GAME_H