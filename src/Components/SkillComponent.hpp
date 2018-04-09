#ifndef SKILL_COMPONENT_H
#define SKILL_COMPONENT_H

#include "../Components/StatusComponent.hpp"
#include "../SkillSet.hpp"
#include <map>
#include <memory>

namespace HJ { namespace Components {

	using namespace Engine;

	enum class SKILL_NAME : int
	{
		BASIC_ATTACK = 0,
		BASIC_DEFENCE = 1,
		SPECIAL_SKILL_1 = 2,
		SPECIAL_SKILL_2 = 3,
		SKILL_INCREASE_HP = 4,
		SKILL_INCREASE_MP = 5
	};

	class SkillComponent : public ECM::Component
	{
		private:
			std::map<SKILL_NAME, std::shared_ptr<Skill>> m_skills;

		public:
			SkillComponent() = delete;
			explicit SkillComponent(ECM::Entity* t_parent);

			SkillComponent* GetType() override;

			void Update(float t_deltaTime) override {}
			void Render() override {}

			void AddSkill(SKILL_NAME t_name, std::shared_ptr<Skill> t_skill);
			std::shared_ptr<Skill> FindSkill(SKILL_NAME t_name);

			std::map<SKILL_NAME, std::shared_ptr<Skill>> GetSkills();
	};

} }

#endif // !SKILL_COMPONENT_H
