#ifndef HARPY_ENCOUNTER_H
#define HARPY_ENCOUNTER_H

#include "BaseEncounter.hpp"

namespace HJ {
	namespace Encounters {

		using namespace Engine;

		class HarpyEncounter final : public BaseEncounterScene
		{
		public:
			HarpyEncounter(GameDataRef t_data);

			void Init() override final;

		private:
			GameDataRef m_data;
		};

	}
}

#endif // !HARPY_ENCOUNTER_H
