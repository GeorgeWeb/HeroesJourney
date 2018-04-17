#ifndef BATTLE_OUTCOME_H
#define BATTLE_OUTCOME_H

#include <Engine/Engine.hpp>
#include "../Game.hpp"
#include "MeetBard.hpp"
#include "MeetRogue.hpp"
#include "MeetSorc.hpp"
#include "FinalStory.hpp"


namespace HJ {

	using namespace Engine;

	class BattleOutcomeScene final : public SM::State
	{
	public:
		BattleOutcomeScene(GameDataRef t_data);

		void Init() override final;

		void HandleInput() override final;
		void Update(float t_delatTime) override final;
		void Draw(float t_deltaTime) override final;

	protected:
		void AddEntity(const std::string& t_name, std::shared_ptr<ECM::Entity> t_entity) override final;

	private:
		GameDataRef m_data;
	
		int m_offset = 0;

		// Sounds & Buffers
		std::shared_ptr<sf::SoundBuffer> m_outBfr;
		sf::Sound m_outSnd;
	};
}

#endif // !BATTLE_OUTCOME_H
