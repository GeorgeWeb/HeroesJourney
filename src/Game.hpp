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
// evils
#include "Entities/EvilFrostMage.hpp"
// buildings
#include "Entities/Infirmary.hpp"
#include "Entities/Blacksmith.hpp"
#include "Entities/Library.hpp"
#include "Entities/Inn.hpp"
#include "Entities/GeneralStore.hpp"

namespace HJ {

	using namespace Engine;

	// [Serializable]
	class GameManager final
	{
		public:
			// amount of gold gathered
			unsigned int gold = 100;
			
			// amount of potions acquired/bought
			unsigned int healthPot = 1;
			unsigned int manaPot = 1;
			
			// encounter's name + the number of times each one is completed.
			std::vector<std::pair<std::string, unsigned int>> unlockedEncounters;
			// this helps manage which heroes are available for the battle,
			// because every hero is related to a particular encounter
			std::vector<std::shared_ptr<Entities::Hero>> unlockedHeroes;

			// resources entities
			std::shared_ptr<ECM::Entity> cHealthPot;
			std::shared_ptr<ECM::Entity> cManaPot;
			std::shared_ptr<ECM::Entity> cGold;

			// good/heroes characters
			std::shared_ptr<Entities::Knight> hKnight;
			std::shared_ptr<Entities::Bard> hBard;
			std::shared_ptr<Entities::Sorceress> hSorceress;
			std::shared_ptr<Entities::Rogue> hRogue;

			// evil/enemies characters
			std::shared_ptr<Entities::EvilFrostMage> eFrostGolem;
			std::shared_ptr<Entities::EvilFrostMage> eFrostMage;

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
			Game(unsigned int t_width, unsigned int t_height, const std::string& t_title, bool t_vsync = true);
			~Game() = default;
		
		private:
			// fires up the game :P (LinkStart ref.: SwordArtsOnline)
			void GameLoop();
	};

	enum class BATTLE_TURN : int
	{
		HERO = 0,
		EVIL = 1
	};

}

#endif !GAME_H