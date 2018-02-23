#include "EncounterPopup.hpp"
#include "../DEFINITIONS.hpp"

namespace HJ { namespace Entities {
	
	EncounterPopup::EncounterPopup() :
		m_bgSprite(AddComponent<Engine::Components::SpriteComponent>("C_PopupBGSprite")),
		m_btnSprite(AddComponent<Engine::Components::SpriteComponent>("C_PopupBtnSprite")),
		m_opponentSprite(AddComponent<Engine::Components::SpriteComponent>("C_PopupOpponentSprite")),
		m_storySprite(AddComponent<Engine::Components::SpriteComponent>("C_PopupStorySprite")),
		m_titleText(AddComponent<Engine::Components::TextComponent>("C_PopupTitleText"))
	{ 
		// by default
		SetVisible(true);
		SetAlive(true);
	}

	void EncounterPopup::Update(float t_deltaTime)
	{
		Entity::Update(t_deltaTime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			std::invoke(OnClose);
			SetForDelete();
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

	void EncounterPopup::SetButtonImage(const sf::Texture& t_texture)
	{
		m_btnSprite->GetSprite().setTexture(t_texture);
		m_btnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
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

	void EncounterPopup::OnCreate(std::function<void()> t_func)
	{
		std::invoke(t_func);
	}

	/*
	void EncounterPopup::SetPosition(sf::Vector2f t_position)
	{
		m_bgSprite->GetSprite().setPosition(t_position);
		m_btnSprite->GetSprite().setPosition(sf::Vector2f((t_position.x - m_btnSprite->GetSprite().getGlobalBounds().width) * 0.5f,
			(t_position.y - m_btnSprite->GetSprite().getGlobalBounds().height) * 0.8f));
		m_opponentSprite->GetSprite().setPosition(sf::Vector2f((t_position.x - m_opponentSprite->GetSprite().getGlobalBounds().width) * 0.5f,
			(t_position.y - m_opponentSprite->GetSprite().getGlobalBounds().height) * 0.5f));
		m_storySprite->GetSprite().setPosition(sf::Vector2f((t_position.x - m_storySprite->GetSprite().getGlobalBounds().width) * 0.1f,
			(t_position.y - m_storySprite->GetSprite().getGlobalBounds().height) * 0.1f));
		m_titleText->GetText().setPosition(sf::Vector2f((t_position.x - m_titleText->GetSprite().getGlobalBounds().width) * 0.5f,
			(t_position.y - m_titleText->GetSprite().getGlobalBounds().height) * 0.1f));
	}
	*/

} }
