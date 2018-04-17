#ifndef MEET_ROGUE_H
#define MEET_ROGUE_H

#include <Engine/Engine.hpp>
#include "../Game.hpp"

#include "../Entities/Dialog.hpp"

namespace HJ {

	using namespace Engine;

	class MeetRogueScene final : public SM::State
	{
	public:
		MeetRogueScene(GameDataRef t_data);

		void Init() override final;

		void HandleInput() override final;
		void Update(float t_delatTime) override final;
		void Draw(float t_deltaTime) override final;

	protected:
		void AddEntity(const std::string& t_name, std::shared_ptr<ECM::Entity> t_entity) override final;

	private:
		GameDataRef m_data;
		std::shared_ptr<Entities::Dialog> m_dialog;
		DIALOG_TURN m_turn;

		int m_offset = 0;
	};
}

#endif // !MEET_ROGUE_H
