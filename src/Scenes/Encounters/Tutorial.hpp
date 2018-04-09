#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <Engine/Engine.hpp>
#include "../../Game.hpp"
#include "../../Entities/Button.hpp"
#include "../../Entities/ActionResolver.hpp"

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
		void NextTurn();

		// evaluates the batte and checks for win/lose condition;
		void Evaluate();

	private:
		GameDataRef m_data;

		
		// ...
		std::vector<std::shared_ptr<Entities::Hero>> m_heroesUnion;
		std::shared_ptr<Entities::Hero> m_activeBoss;
		std::shared_ptr<Entities::ActionResolver> m_actionResolver;

		// ...
		BATTLE_TURN m_turn;
		BATTLE_STATUS m_status;
		
		// ...
		std::vector<Engine::Components::SpriteComponent*> m_allUIcomps;
		std::vector<Engine::Components::SpriteComponent*> m_battleUIButtons;
		
		// ...
		std::vector<std::shared_ptr<Entities::Hero>> m_activeHeroes;
		std::shared_ptr<Entities::Hero> m_heroOnTurn = nullptr;

		// ...
		int m_hTurnCount;
		unsigned int m_heroDeathCount = 0;
		unsigned int m_evilDeathCount = 0;
		// hero on turn being chosen indicator
		bool chosen = false;

		// indicator who's turn it is
		std::string m_charOnTurn = "";

		// ...
		bool isEvalComplete;
	};
} }

#endif // !TUTORIAL_H
