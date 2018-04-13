#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "BaseEncounter.hpp"

namespace HJ { namespace Encounters {

	using namespace Engine;

	class TutorialScene : public BaseEncounterScene
	{
		public:
			TutorialScene(GameDataRef t_data);

			void Init() override final;

		//private:
			//GameDataRef m_data;
	};

} }

#endif // !TUTORIAL_H
