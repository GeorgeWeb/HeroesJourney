#include "EncounterPopup.hpp"
#include "../DEFINITIONS.hpp"
#include "../Controls.hpp"

#include <Engine/Engine.hpp>

namespace HJ { namespace Entities {
	
	using namespace Engine;
	using namespace Engine::System;
	using namespace Engine::Input;
	using namespace Engine::ECM;
	using namespace Engine::Components;

	EncounterPopup::EncounterPopup() :
		m_bgSprite(AddComponent<SpriteComponent>("C_zPopupBGSprite")),
		m_closeBtnSprite(AddComponent<SpriteComponent>("C_xPopupCloseBtnSprite")),
		m_playBtnSprite(AddComponent<SpriteComponent>("C_xPopupPlayBtnSprite")),
		m_opponentSprite(AddComponent<SpriteComponent>("C_xPopupOpponentSprite")),
		m_storySprite(AddComponent<SpriteComponent>("C_xPopupStorySprite")),
		m_titleText(AddComponent<TextComponent>("C_aPopupTitleText"))
	{ 
		showOnCreate = false;
	}

	void EncounterPopup::Init()
	{
		// defaults
		SetAlive(false);
		SetVisible(false);
		m_closeBtnSprite->SetClickable(false); ///> true by default
		m_playBtnSprite->SetClickable(false);

		m_bgSprite->independent = true;
		m_closeBtnSprite->independent = true;
		m_playBtnSprite->independent = true;
		m_opponentSprite->independent = true;
		m_storySprite->independent = true;
		m_titleText->independent = true;
	}

	EncounterPopup* EncounterPopup::GetType()
	{
		return this;
	}

	void EncounterPopup::Update(float t_deltaTime)
	{
		Entity::Update(t_deltaTime);

		// check for key press or click for closing
		if (m_closeBtnSprite->IsClickable() && m_encInput.isClicked(m_closeBtnSprite->GetSprite(), Controls::GetButton("Select"), Engine2D::GetWin()))
		{
			SetAlive(false);
			SetVisible(false);
			std::invoke(OnClose);
		}

		if (m_playBtnSprite->IsClickable() && m_encInput.isClicked(m_playBtnSprite->GetSprite(), Controls::GetButton("Select"), Engine2D::GetWin()))
		{
			std::invoke(OnPlay);
		}
	}

	void EncounterPopup::Render()
	{
		Entity::Render();
	}

	void EncounterPopup::ToggleButtonsBehaviour()
	{
		m_closeBtnSprite->SetClickable(!m_closeBtnSprite->IsClickable());
		m_playBtnSprite->SetClickable(!m_playBtnSprite->IsClickable());
	}

	void EncounterPopup::SetBackgroundImage(const sf::Texture& t_texture)
	{
		m_bgSprite->GetSprite().setTexture(t_texture);
		m_bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
	}

	void EncounterPopup::SetCloseButtonImage(const sf::Texture & t_texture)
	{
		m_closeBtnSprite->GetSprite().setTexture(t_texture);
		m_closeBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
	}

	void EncounterPopup::SetPlayButtonImage(const sf::Texture& t_texture)
	{
		m_playBtnSprite->GetSprite().setTexture(t_texture);
		m_playBtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
	}

	void EncounterPopup::SetOpponentImage(const sf::Texture& t_texture)
	{
		m_opponentSprite->GetSprite().setTexture(t_texture, true);
		m_opponentSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
	}

	void EncounterPopup::SetStoryImage(const sf::Texture& t_texture)
	{
		m_storySprite->GetSprite().setTexture(t_texture);
		m_storySprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
	}

	void EncounterPopup::SetTitleText(const std::string& t_text, const sf::Font& t_font)
	{
		m_titleText->SetFont(t_font);
		m_titleText->GetText().setString(t_text);
		m_titleText->GetText().setCharacterSize(22);
		m_titleText->GetText().setStyle(sf::Text::Bold);
	}

	void EncounterPopup::OnDisplay(std::function<void()> t_func)
	{
		std::invoke(t_func);
	}

	void EncounterPopup::Assemble(sf::Vector2f t_position)
	{
		m_bgSprite->GetSprite().setPosition(t_position);

		m_playBtnSprite->GetSprite().setPosition(sf::Vector2f(t_position.x * 2.15f, t_position.y * 5.025f));

		m_closeBtnSprite->GetSprite().setPosition(sf::Vector2f(t_position.x * 2.990f, t_position.y*1.1f));

		m_opponentSprite->GetSprite().scale(2.8f, 2.8f);
		m_opponentSprite->GetSprite().setPosition(sf::Vector2f(t_position.x * 2.1f, t_position.y * 1.9f));

		m_storySprite->GetSprite().setPosition(sf::Vector2f(t_position.x * 1.1f, t_position.y * 1.7f));

		m_titleText->GetText().setPosition(sf::Vector2f(t_position.x * 1.65f, t_position.y * 1.25f));
	}

} }
