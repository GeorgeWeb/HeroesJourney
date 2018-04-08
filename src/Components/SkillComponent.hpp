#ifndef SKILL_COMPONENT_H
#define SKILL_COMPONENT_H

#include "../Components/StatusComponent.hpp"
#include "../SkillSet.hpp"
#include <vector>
#include <memory>

namespace HJ { namespace Components {

	using namespace Engine;

	class SkillComponent : public ECM::Component
	{
		private:
			std::vector<EFFECT_TYPE> applicableEffects;

		public:
			SkillComponent() = delete;
			explicit SkillComponent(ECM::Entity* t_parent);

			SkillComponent* GetType() override;

			void Update(float t_deltaTime) override;
			void Render() override;

			std::vector<EFFECT_TYPE> GetApplicableEffects();
	};

} }

#endif // !SKILL_COMPONENT_H
