#ifndef CASTLESCENE_H
#define CASTLESCENE_H

#include <Engine/Engine.hpp>
#include "../Game.hpp"
#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/TextComponent.hpp>


namespace HJ {

	using namespace Engine;

	class CastleScene final : public SM::State
	{
	public:
		CastleScene(GameDataRef t_data);

		void Init() override final;

		void HandleInput() override final;
		void Update(float t_delatTime) override final;
		void Draw(float t_deltaTime) override final;

	private:
		GameDataRef m_data;

		//boolean click checks
		bool m_infirmaryClick = false;
		bool m_blacksmithClick = false;
		bool m_libraryClick = false;
		bool m_innClick = false;
		bool m_generalStore = false;
		bool m_backClick = false;

		//unclick checks
		bool m_infirmaryUnClick = false;
		bool m_blacksmithUnClick = false;
		bool m_libraryUnClick = false;
		bool m_innUnClick = false;
		bool m_generalUnStore = false;
		bool m_backUnClick = false;

		sf::Clock m_clock;
		float m_time = 0.1f;
		// Entities

	};
}

#endif // !CASTLESCENE_H
