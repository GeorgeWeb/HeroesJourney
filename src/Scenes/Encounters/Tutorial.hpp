#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <Engine/Engine.hpp>
#include "../../Game.hpp"

#include <Engine/ECM/Components/SpriteComponent.hpp>

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
		void DisableUIButtons(std::vector<Engine::Components::SpriteComponent*> t_buttons);
		void EnableUIButtons(std::vector<Engine::Components::SpriteComponent*> t_buttons);
		void CheckForHeroicDeath(std::vector<Engine::Components::SpriteComponent*> t_buttons);
		void CheckForBattleOutcome(std::vector<Engine::Components::SpriteComponent*> t_buttons);
		void NextTurn();
		void ResetActiveHeroes();

	private:
		GameDataRef m_data;
		
		BATTLE_TURN m_turn;
		BATTLE_STATUS m_status;
		
		std::vector<std::shared_ptr<Entities::Hero>> m_activeHeroes;
		std::shared_ptr<Entities::Hero> m_heroOnTurn = nullptr;
		unsigned int m_hTurnCount;
		unsigned int m_hDeathCount = 0;
		
		// helpful for battle outcome
		float m_condTimer;
	};
} }

#endif // !TUTORIAL_H
