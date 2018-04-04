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
		void DisableUIButtons(std::vector<Components::SpriteComponent*> t_buttons);
		void EnableUIButtons(std::vector<Components::SpriteComponent*> t_buttons);

	private:
		GameDataRef m_data;
		BATTLE_TURN m_turn;

		unsigned int m_hCount;
		bool m_won = false;
	};
} }

#endif // !TUTORIAL_H
