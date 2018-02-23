#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <Engine/Engine.hpp>
#include <Engine/ECM/Components/SpriteComponent.hpp>
#include "CastleInterior.hpp"

#include "../Game.hpp"
#include "../Entities/EncounterPopup.hpp"

namespace HJ {

	using namespace Engine;

	class MapScene final : public SM::State
	{
	public:
		MapScene(GameDataRef t_data);

		void Init() override final;

		void HandleInput() override final;
		void Update(float t_delatTime) override final;
		void Draw(float t_deltaTime) override final;

	private:
		GameDataRef m_data;

		//boolean click checks
		bool m_castleClick = false;
		bool m_forestClick = false;
		bool m_mountainsClick = false;
		bool m_seaClick = false;
		bool m_evilCastleClick = false;

		//unclick checks
		bool m_castleUnClick = false;
		bool m_forestUnClick = false;
		bool m_mountainsUnClick = false;
		bool m_seaUnClick = false;
		bool m_evilCastleUnClick = false;

		sf::Clock m_clock;
		float m_time = 0.1f;

		/* ENTITIES */

		// Encounters popups
		std::shared_ptr<Entities::EncounterPopup> m_encounterPopup;
	};
}

#endif // !MAPSCENE_H
