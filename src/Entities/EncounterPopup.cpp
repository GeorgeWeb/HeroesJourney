#include "EncounterPopup.hpp"
#include "../DEFINITIONS.hpp"

#include <Engine/System/Renderer.hpp>

namespace HJ { namespace Entities {
	
	using namespace Engine::System;
	using namespace Engine::Input;

	EncounterPopup::EncounterPopup() :
		m_bgSprite(AddComponent<Engine::Components::SpriteComponent>("C_PopupBGSprite")),
		m_closeBtnSprite(AddComponent<Engine::Components::SpriteComponent>("C_PopupCloseBtnSprite")),
		m_playBtnSprite(AddComponent<Engine::Components::SpriteComponent>("C_PopupPlayBtnSprite")),
		m_opponentSprite(AddComponent<Engine::Components::SpriteComponent>("C_PopupOpponentSprite")),
		m_storySprite(AddComponent<Engine::Components::SpriteComponent>("C_PopupStorySprite")),
		m_titleText(AddComponent<Engine::Components::TextComponent>("C_PopupTitleText"))
	{ 
		// by default
		SetVisible(false);
		SetAlive(false);
	}

	EncounterPopup* EncounterPopup::GetType()
	{
		return this;
	}

	void EncounterPopup::Update(float t_deltaTime)
	{
		Entity::Update(t_deltaTime);

		// check for key press or click for closing
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || 
		   (m_closeBtnSprite->IsClickable() && m_encInput.isClicked(m_closeBtnSprite->GetSprite(), sf::Mouse::Left, Renderer::GetWin())))
		{
			SetAlive(false);
			SetVisible(false);
			std::invoke(OnClose);
		}
	}

	void EncounterPopup::Render()
	{
		Entity::Render();
	}

	void EncounterPopup::SetBackgroundImage(const sf::Texture& t_texture)
	{
		m_bgSprite->GetSprite().setTexture(t_texture);
		m_bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
	}

	void EncounterPopup::SetCloseButtonImage(const sf::Texture & t_texture)
	{
	}

	void EncounterPopup::SetPlayButtonImage(const sf::Texture& t_texture)
	{
		m_playBtnSprite->GetSprite().setTexture(t_texture);
		m_playBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
	}

	void EncounterPopup::SetOpponentImage(const sf::Texture& t_texture)
	{
		m_opponentSprite->GetSprite().setTexture(t_texture);
		m_opponentSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
	}

	void EncounterPopup::SetStoryImage(const sf::Texture& t_texture)
	{
		m_storySprite->GetSprite().setTexture(t_texture);
		m_storySprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
	}

	void EncounterPopup::SetTitleText(const std::string& t_text, const sf::Font t_font)
	{
		m_titleText->GetText().setString(t_text);
		m_titleText->GetText().setCharacterSize(30);
	}

	void EncounterPopup::OnDisplay(std::function<void()> t_func)
	{
		std::invoke(t_func);
	}

	void EncounterPopup::Assemble(sf::Vector2f t_position)
	{
		m_bgSprite->GetSprite().setPosition(t_position);
		m_playBtnSprite->GetSprite().setPosition(sf::Vector2f((t_position.x - m_playBtnSprite->GetSprite().getGlobalBounds().width) * 0.5f,
			(t_position.y - m_playBtnSprite->GetSprite().getGlobalBounds().height) * 0.8f));
		m_opponentSprite->GetSprite().setPosition(sf::Vector2f((t_position.x - m_opponentSprite->GetSprite().getGlobalBounds().width) * 0.5f,
			(t_position.y - m_opponentSprite->GetSprite().getGlobalBounds().height) * 0.5f));
		m_storySprite->GetSprite().setPosition(sf::Vector2f((t_position.x - m_storySprite->GetSprite().getGlobalBounds().width) * 0.1f,
			(t_position.y - m_storySprite->GetSprite().getGlobalBounds().height) * 0.1f));
		m_titleText->GetText().setPosition(sf::Vector2f((t_position.x - m_titleText->GetText().getGlobalBounds().width) * 0.5f,
			(t_position.y - m_titleText->GetText().getGlobalBounds().height) * 0.1f));
	}

} }
