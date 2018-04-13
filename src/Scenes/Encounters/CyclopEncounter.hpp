#ifndef CYCLOP_ENCOUNTER_H
#define CYCLOP_ENCOUNTER_H

#include "BaseEncounter.hpp"

namespace HJ { namespace Encounters {

	using namespace Engine;

	class CyclopEncounter final : public BaseEncounterScene
	{
	public:
		CyclopEncounter(GameDataRef t_data);

		void Init() override final;

	private:
		GameDataRef m_data;
	};

} }

#endif // !CYCLOP_ENCOUNTER_H
