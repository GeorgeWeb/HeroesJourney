#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <Engine/Engine.hpp>
#include "../../Game.hpp"

//#include <Engine/ECM/Components/SpriteComponent.hpp>
#include "../../Entities/Button.hpp"

namespace HJ { namespace Encounters {

	using namespace Engine;

	class TutorialScene final : public SM::State
	{
	public:
		TutorialScene(GameDataRef t_data);

		void Init() override final;

		void HandleInput() override final;
		void Update(float t_delatTime) override final;
		void Draw(float t_deltaTime) override final;

	protected:
		void AddEntity(const std::string& t_name, std::shared_ptr<ECM::Entity> t_entity) override final;

	private:
		void DisableUIButtons();
		void EnableUIButtons();
		void UpdateUI();
		void CheckForDeaths();
		void CheckForBattleOutcome();
		void NextTurn();

		void HandleHeroActions(const sf::Vector2f& t_initPos);

	private:
		GameDataRef m_data;
		
		BATTLE_TURN m_turn;
		BATTLE_STATUS m_status;
		
		std::vector<Engine::Components::SpriteComponent*> m_allUIcomps;
		std::vector<Engine::Components::SpriteComponent*> m_battleUIButtons;
		std::vector<std::shared_ptr<Entities::Hero>> m_activeHeroes;
		std::shared_ptr<Entities::Hero> m_heroOnTurn = nullptr;
		int m_hTurnCount;
		unsigned int m_hDeathCount = 0;
		// hero on turn being chosen indicator
		bool chosen = false;

		// AI turn preparation
		sf::Clock m_EnemyStepTime;
		bool m_finishedPrep = false;

		// hero turn preparation
		bool heroStepIn = false;
		bool heroReturn = false;

		// indicator who's turn it is
		std::string m_charOnTurn = "";
	};
} }

#endif // !TUTORIAL_H
