#include "ClickableComponent.hpp"
#include "../../System/Renderer.hpp"
#include <string>

const std::string btn_click_snd = "res/music/sounds/button-click.wav";

namespace Engine { namespace Components {

	using namespace System;

	ClickableComponent::ClickableComponent(ECM::Entity* t_parent) :
		m_isClicked(false),
		m_unClicked(false),
		m_canResolve(false),
		m_timer(0.1f),
		Component(t_parent)
	{
		SetClickable(true);
	}

	ClickableComponent* ClickableComponent::GetType()
	{
		return this;
	}

	void ClickableComponent::SetSpriteTarget(SpriteComponent* t_sprite)
	{
		m_spriteComponent = std::move(std::make_shared<SpriteComponent>(*t_sprite));
	}

	void ClickableComponent::Update(float t_deltaTime)
	{			
		if (m_parent->IsAlive())
		{
			if (m_isClicked && !m_unClicked)
			{
				// play click sound
				static Asset::AssetManager assets;
				m_clickBfr = assets.LoadBuffer(btn_click_snd);
				m_clickSnd.setBuffer(*m_clickBfr);
				m_clickSnd.play();

				// change color on click
				m_spriteComponent->GetSprite().setColor(sf::Color(
					m_spriteComponent->GetSprite().getColor().r - 100,
					m_spriteComponent->GetSprite().getColor().g - 100,
					m_spriteComponent->GetSprite().getColor().b - 100,
					m_spriteComponent->GetSprite().getColor().a));

				m_unClicked = true;
			}

			if (m_unClicked)
			{
				m_timer -= t_deltaTime;
			}

			if (m_timer < 0.0f && m_unClicked)
			{
				// change color back to normal after unclicked
				m_spriteComponent->GetSprite().setColor(sf::Color(
					m_spriteComponent->GetSprite().getColor().r + 100,
					m_spriteComponent->GetSprite().getColor().g + 100,
					m_spriteComponent->GetSprite().getColor().b + 100,
					m_spriteComponent->GetSprite().getColor().a));

				m_timer = 0.1f;
				m_unClicked = false;
				m_isClicked = false;
				m_canResolve = true;
			}
		}
	}

	void ClickableComponent::SetResolve(bool t_resolve)
	{
		m_canResolve = t_resolve;
	}

	bool ClickableComponent::CanResolve()
	{
		return m_canResolve;
	}

} }