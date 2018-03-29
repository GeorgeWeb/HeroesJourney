#include "SpriteComponent.hpp"
#include "../../System/Renderer.hpp"

namespace Engine { namespace Components {

	SpriteComponent::SpriteComponent(ECM::Entity* t_parent) :
		Component(t_parent),
		m_sprite(std::make_shared<sf::Sprite>())
	{ 
		SetClickable(true);
	}

	SpriteComponent* SpriteComponent::GetType()
	{
		return this;
	}

	void SpriteComponent::Update(float t_deltaTime)
	{
		// set pos to the parent's one for ONLY non-independent sprite components
		if (m_parent->IsAlive() && !independent)
		{
			m_sprite->setPosition(m_parent->GetPosition());
		}
	}

	void SpriteComponent::Render()
	{
		if (m_parent->IsVisible())
			Engine::System::Renderer::Queue(&(*m_sprite));
	}

	sf::Sprite& SpriteComponent::GetSprite()
	{
		return *m_sprite;
	}

} }