#include "AnimatorComponent.hpp"

namespace Engine { namespace Components {

	using namespace System;

	AnimatorComponent::AnimatorComponent(ECM::Entity* t_parent) :
		Component(t_parent)
	{
		SetClickable(false);
	}

	AnimatorComponent* AnimatorComponent::GetType()
	{
		return this;
	}

	void AnimatorComponent::Update(float t_deltaTime)
	{
		if (m_parent->IsAlive())
		{
			for (const auto& anim : m_animations)
				anim.second->Update(t_deltaTime);
		}
	}

	void AnimatorComponent::Render()
	{
		// Do not do anything
	}

	std::shared_ptr<Animation> AnimatorComponent::AddAnimation(const std::string& t_name, Animation t_animation)
	{
		// TODO: VALIDATION CHECKS if name exists in!!!
		std::shared_ptr<Animation> anim(std::make_shared<Animation>(Animation(t_animation)));
		m_animations.insert_or_assign(t_name, anim);
		return anim;
	}

	sf::IntRect AnimatorComponent::GetAnimUVRect(const std::string& t_name)
	{
		return m_animations["Anim_HeroFull"]->uvRect;
	}

	std::map<std::string, std::shared_ptr<Animation>> AnimatorComponent::GetAnims()
	{
		return m_animations;
	}

	Animation& AnimatorComponent::GetAnimation(const std::string& t_name)
	{
		// TODO: VALIDATION FOR EXISTENCE !!!
		return *m_animations[t_name];
	}



} }