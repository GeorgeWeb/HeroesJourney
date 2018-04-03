#ifndef ENCOUNTER_CREATOR_COMPONENT
#define ENCOUNTER_CREATOR_COMPONENT

#include <Engine/ECM/ECM.hpp>

namespace HJ { namespace Components {

	using namespace Engine;

	class EncounterCreatorComponent final : public ECM::Component
	{
		protected:
			// ...
		public:
			EncounterCreatorComponent() = delete;
			explicit EncounterCreatorComponent(ECM::Entity* t_parent);

			EncounterCreatorComponent* GetType() override;
			
			void Update(float t_deltaTime) override;
			void Render() override;
	};

} }

#endif // !ENCOUNTER_CREATOR_COMPONENT
