#ifndef TROLL_ENCOUNTER_H
#define TROLL_ENCOUNTER_H

#include "BaseEncounter.hpp"

namespace HJ {
	namespace Encounters {

		using namespace Engine;

		class TrollEncounter final : public BaseEncounterScene
		{
		public:
			TrollEncounter(GameDataRef t_data);

			void Init() override final;

		private:
			GameDataRef m_data;
		};

	}
}

#endif // !TROLL_ENCOUNTER_H