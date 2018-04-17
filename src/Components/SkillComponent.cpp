#include "SkillComponent.hpp"

namespace HJ { namespace Components {

	using namespace Engine;

	SkillComponent::SkillComponent(ECM::Entity* t_parent)
		: ECM::Component(t_parent)
	{ }

	SkillComponent* SkillComponent::GetType()
	{
		return this;
	}

	void SkillComponent::AddSkill(SKILL_NAME t_name, std::shared_ptr<Skill> t_skill)
	{
		m_skills.insert_or_assign(t_name, t_skill);
	}

	std::shared_ptr<Skill> SkillComponent::FindSkill(SKILL_NAME t_name)
	{
		auto skill = m_skills.find(t_name);
		if (skill != m_skills.end())
			return skill->second;
		else
			return nullptr;
	}

	std::map<SKILL_NAME, std::shared_ptr<Skill>> SkillComponent::GetSkills()
	{
		return m_skills;
	}

} }