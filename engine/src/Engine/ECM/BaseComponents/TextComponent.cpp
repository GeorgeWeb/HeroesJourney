#include "TextComponent.hpp"
#include "../../System/Renderer.hpp"

namespace Engine { namespace Components {

	TextComponent::TextComponent(ECM::Entity* t_parent) :
		Component(t_parent),
		m_text(std::make_shared<sf::Text>())
	{ }

	void TextComponent::Update(float t_deltaTime)
	{
		if (m_parent->IsAlive())
		{
			m_text->setPosition(m_parent->GetPosition());
			m_text->setRotation(m_parent->GetRotation());
		}
	}

	void TextComponent::Render()
	{
		if (m_parent->IsVisible())
			Engine::System::Renderer::Queue(&(*m_text));
	}

	sf::Text& TextComponent::GetText()
	{
		return *m_text;
	}

} }