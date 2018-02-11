#include "SpriteComponent.hpp"
#include "../../System/Renderer.hpp"

namespace Engine { namespace Components {

	SpriteComponent::SpriteComponent(ECM::Entity* t_parent) :
		Component(t_parent),
		m_sprite(std::make_shared<sf::Sprite>())
	{ }

	void SpriteComponent::Update(float t_deltaTime)
	{
		if (m_parent->IsAlive())
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