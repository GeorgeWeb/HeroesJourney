#ifndef FROST_MAGE_ENCOUNTER_H
#define FROST_MAGE_ENCOUNTER_H

#include "BaseEncounter.hpp"

namespace HJ {
	namespace Encounters {

		using namespace Engine;

		class FinalBossFMEncounter final : public BaseEncounterScene
		{
		public:
			FinalBossFMEncounter(GameDataRef t_data);

			void Init() override final;

		//private:
			//GameDataRef m_data;
		};

	}
}

#endif // !FROST_MAGE_ENCOUNTER_H
