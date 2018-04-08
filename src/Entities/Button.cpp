#include "Button.hpp"
#include <Engine/Engine.hpp>

namespace HJ { namespace Entities {

	using namespace Engine;
	using namespace Engine::System;
	using namespace Engine::Input;
	using namespace Engine::ECM;
	using namespace Engine::Components;

	Button::Button() :
		m_sprite(AddComponent<SpriteComponent>("C_bButtonSprite")),
		m_text(AddComponent<TextComponent>("C_aButtonText")),
		m_click(AddComponent<ClickableComponent>("C_ButtonClick"))
	{ 
		m_click->SetSpriteTarget(m_sprite.get());
	}

	Button* Button::GetType()
	{
		return this;
	}

	void Button::Init()
	{
		// defaults
		SetAlive(true);
		SetVisible(true);
		// center the text
		m_text->independent = true;
		m_text->GetText().setPosition(GetPosition());
	}

	void Button::Update(float t_deltaTime)
	{
		Entity::Update(t_deltaTime);
	}

	void Button::Render()
	{
		Entity::Render();
	}

} }