#include "SkillComponent.hpp"

namespace HJ { namespace Components {

	using namespace Engine;

	SkillComponent::SkillComponent(ECM::Entity* t_parent)
		: ECM::Component(t_parent)
	{
		
	}

	SkillComponent* SkillComponent::GetType()
	{
		return this;
	}

	void SkillComponent::Update(float t_deltaTime)
	{
	}

	void SkillComponent::Render()
	{
	}

	std::vector<EFFECT_TYPE> SkillComponent::GetApplicableEffects()
	{
		return applicableEffects;
	}

} }