#include "TextComponent.hpp"
#include "../../System/Renderer.hpp"

namespace Engine { namespace Components {

	TextComponent::TextComponent(ECM::Entity* t_parent) :
		Component(t_parent),
		m_text(std::make_shared<sf::Text>())
	{ 
		SetClickable(true);
	}

	TextComponent* TextComponent::GetType()
	{
		return this;
	}

	void TextComponent::Update(float t_deltaTime)
	{
		// set pos to the parent's one for ONLY non-independent text components
		if (m_parent->IsAlive() && !independent)
			m_text->setPosition(m_parent->GetPosition());
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