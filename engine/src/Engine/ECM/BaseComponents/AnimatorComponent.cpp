#include "AnimatorComponent.hpp"

namespace Engine { namespace Components {

	AnimatorComponent::AnimatorComponent(ECM::Entity* t_parent) :
		Component(t_parent),
		m_animation(std::make_shared<System::Animation>())
	{ }

	void AnimatorComponent::Update(float t_deltaTime)
	{
		if (m_parent->IsAlive())
		{
			m_animation->Update(t_deltaTime);
		}
	}

	void AnimatorComponent::Render()
	{
		// Do not do anything
	}

	void AnimatorComponent::SetAnimation(sf::Texture* t_texture, sf::Vector2u t_imgCount, float t_switchTime)
	{
		m_animation.reset(new System::Animation(t_texture, t_imgCount, t_switchTime));
	}

	System::Animation& AnimatorComponent::GetAnimation()
	{
		return *m_animation;
	}



} }